#include <Arduino.h>

//déclaration variable



        int PIN1=A1;
        int PIN2=A2;
        int PIN3=A3;
        int PIN4=A4;

    //coef de la fonction des capteurs:
        int  Coef1= 5;
    //coef des valeur axiales:
        int  Kaxe = 50;
    //mesure du capteur a vide
        int  VX1   = analogRead(PIN1);
        int  VX2   = analogRead(PIN2);
        int  VX3   = analogRead(PIN3);
        int  VX4   = analogRead(PIN4);
        //mesure valeur capteur
            
        float V1,V2,V3,V4;
        float moydifx,moydify;

        float moyv1;
        float oldv14;
        float oldv13;
        float oldv12;
        float oldv11;
        float moyv2;
        float oldv24;
        float oldv23;
        float oldv22;
        float oldv21;
        float moyv3;
        float oldv34;
        float oldv33;
        float oldv32;
        float oldv31;
        float moyv4;
        float oldv44;
        float oldv43;
        float oldv42;
        float oldv41;
        float moydifxx;
        float olddifx5;
        float olddifx4;
        float olddifx3;
        float olddifx2;
        float olddifx1;
        float moydifyx;
        float olddify5;
        float olddify4;
        float olddify3;
        float olddify2;
        float olddify1;

void setup() {
  // put your setup code here, to run once:
        //positions of sensors
        //  1----x----2    |
        //  |    ^    |    |
        //  |    |    y    |--y---|  x
        //  |    |    |    |      |
        //  3---------4    4      2
        //  .---------.
    //déclaration entré/sortie:   

    //initalise Serial port
        Serial.begin(9600);
        Serial.println("fauteuil 9000 initialized");
}

void loop() {
  // put your main code here, to run repeatedly:
    //mesure valeur capteur
        V1 = analogRead(A1);
        V2 = analogRead(A2);
        V3 = analogRead(A3);
        V4 = analogRead(A4);
        moyv1=(V1+oldv11+oldv12+oldv13+oldv14)/5;
        oldv14=oldv13;
        oldv13=oldv12;
        oldv12=oldv11;
        oldv11=V1-VX1;
        moyv2=(V2+oldv21+oldv22+oldv23+oldv24)/5;
        oldv24=oldv23;
        oldv23=oldv22;
        oldv22=oldv21;
        oldv21=V2-VX2;
        moyv3=(V3+oldv31+oldv32+oldv33+oldv34)/5;
        oldv34=oldv33;
        oldv33=oldv32;
        oldv32=oldv31;
        oldv31=V3-VX3;
        moyv4=(V4+oldv41+oldv42+oldv43+oldv44)/5;
        oldv44=oldv43;
        oldv43=oldv42;
        oldv42=oldv41;
        oldv41=V4-VX4;
        moydifx=(olddifx1+olddifx2+olddifx3+olddifx4+olddifx5)/5;
        olddifx5=olddifx4;
        olddifx4=olddifx3;
        olddifx3=olddifx2;
        olddifx2=olddifx1;
        olddifx1=moyv1+moyv2-moyv3-moyv4;
        moydify=(olddify1+olddify2+olddify3+olddify4+olddify5)/5;
        olddify5=olddify4;
        olddify4=olddify3;
        olddify3=olddify2;
        olddify2=olddify1;
        olddify1=moyv2+moyv4-moyv1-moyv3;

    //transmettre résultat
        Serial.print("X=");
        Serial.println(moydifx);
        Serial.print("Y=");
        Serial.println(moydifx);

    delay(30);
}
