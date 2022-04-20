#include <Arduino.h>


void setup() {
  Serial.begin(9600);

}



void loop() {
  

    int x1,x2,x3,x4,x5;
    x1=1;
    x2=2;
    x3=3;
    x4=4;
    x5=5;

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

    char payload[JSonString.length()];

    int i;
    for (i = 0; i < sizeof(payload); i++) {
        payload[i] = JSonString[i];

    }
    Serial.printf(payload);

    delay(5000);

}

 
