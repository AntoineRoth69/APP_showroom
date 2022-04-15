#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h> 

//-------- your wifi -----------

const char* ssid = "CELERITY_MONTALVAN";
const char* password = "1722510060B.";

#define ORG "5hjcib" 
#define DEVICE_TYPE "raspberry1" 
#define DEVICE_ID "comunicacioniot" 
#define TOKEN "123456789Bf" 
//-------- Bluemix information to build up MQTT message -------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
// this part I need to know how to subscribe to topics that IBM WATSON sends me
char pubTopic[] = "iot-2/evt/status/fmt/json";
char subTopic[] = "iot-2/cmd/test/fmt/String";


char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

const char ledpin3 = 4;

void receivedCallback(char* pubTopic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println (pubTopic);

  Serial.print("payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  /* we got '1' -> on */
  if ((char)payload[0] == '1') {
    digitalWrite(ledpin3, HIGH); 
  } else {
    /* we got '0' -> on */
    digitalWrite(ledpin3, LOW);
  }
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    pinMode(ledpin3, OUTPUT);
    Serial.print("Connecting to "); 
    Serial.print(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    
    Serial.print("WiFi connected, IP address: "); 
    Serial.println(WiFi.localIP());

    if (!client.connected()) {
        Serial.print("Reconnecting client to ");
        Serial.println(server);
        while (!client.connect(clientId, authMethod, token)) {
            Serial.print(".");
            delay(500);
        }
        client.setCallback(receivedCallback);
        if (client.subscribe(subTopic)) {
            Serial.println("subscribe to cmd OK");
        } else {
            Serial.println("subscribe to cmd FAILED");
        }
        Serial.println("Bluemix connected");
    }
}


void loop() {
    client.loop();

        if (client.publish(pubTopic, (char*) payload.c_str())) {
            Serial.println("Publish ok");
        } else {
            Serial.println("Publish failed");
        }
    }
}