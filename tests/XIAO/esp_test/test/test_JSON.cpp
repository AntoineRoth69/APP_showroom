#include <WiFi.h>
#include <PubSubClient.h>


// Update these with values suitable for your network.
const char* ssid = "showroom";
const char* password = "wt0meevfc6";
const char* mqtt_server = "10.100.100.117";
#define mqtt_port 443
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define MQTT_SERIAL_PUBLISH_CH "/showroom/PIR"
#define MQTT_SERIAL_RECEIVER_CH "/showroom/PIR"
#define MQTT_TEST "HELLO "

WiFiClient wifiClient;

PubSubClient client(wifiClient);


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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish(MQTT_SERIAL_PUBLISH_CH, "hello world");
      // ... and resubscribe
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();


}

void publishData(String data){
  if (!client.connected()) {
    reconnect();
  }
    char payload[data.length()];

    int i;
    for (i = 0; i < sizeof(payload); i++) {
        payload[i] = data[i];

    }

    client.publish(MQTT_SERIAL_PUBLISH_CH, payload);
}
void loop() {
  
    client.loop();

    int x1,x2,x3,x4,x5;

    //Capteur 1
    String JSonString = "[{\"PIR1\":";
    JSonString += x1;
    JSonString += "},";

    //Capteur 2
    JSonString += "{\"PIR2\":";
    JSonString += x2;
    JSonString += "},";

    //Capteur 3
    JSonString += "{\"PIR3\":";
    JSonString += x3;
    JSonString += "},";

    //Capteur 4
    JSonString += "{\"PIR4\":";
    JSonString += x4;
    JSonString += "},";

    //Capteur 5
    JSonString += "{\"PIR5\":";
    JSonString += x5;
    JSonString += "}]";

    publishData(JSonString);
    delay(5000);

}

 
