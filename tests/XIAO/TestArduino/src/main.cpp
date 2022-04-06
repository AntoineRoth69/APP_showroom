#include <Arduino.h>

//const
#define high 275
#define low 200

//alim en 3,3V
const int xpin = A2;
double x;
boolean Res1;
int Res2;

//fontion decla
boolean filtreTest(double a);
void filtreTest2(double a, int b);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //lecture filtre
  x=analogRead(xpin);
  Res1= filtreTest(x);
  filtreTest2(x,Res2);


  //affichage
  //Serial.println(x);
  Serial.println(Res1);
  //Serial.println(Res2);
  delay(50);

}

//fonctions
boolean filtreTest(double a){

  if ((a<low) || (a>high))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void filtreTest2(double a, int b){

  if ((a<low) || (a>high))
  {
     b=1;
  }
  else
  {
    b=0;
  }
}


