

#include <WiFi.h>
#include <PubSubClient.h>


// Replace the next variables with your SSID/Password combination
const char* ssid = "showroom";
const char* password = "wt0meevfc6";

// Add your MQTT Broker IP address, example:
const char* mqtt_server = "10.100.100.117";

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect();
void setup_wifi();
void callback(char* topic, byte* message, unsigned int length);



void setup() {
  Serial.begin(115200);
  // default settings

  setup_wifi();
  client.setServer(mqtt_server, 443);
  client.setCallback(callback);
  


}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("/showroom/PIR");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    double humidity= 15;
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("/showroom/PIR", humString);
  
}