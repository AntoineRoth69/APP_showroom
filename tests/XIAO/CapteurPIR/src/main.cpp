#include <Arduino.h>

//const
#define high 275
#define low 200
#define high2 449
#define low2 0

//alim en 3,3V
const int xpin = A2;
int g1=100;
int g2=200;
double x;
boolean Res1;
boolean Res2;
int s1,s2;

//fontion decla
boolean filtreTest(double a);
boolean filtreTest2(double a);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //lecture filtre
  x=analogRead(xpin);
  Res1= filtreTest(x);
  Res2=filtreTest2(x);

  s1=Res1*g1;
  s2=Res2*g2;

  //affichage
  //Serial.print(x);
  //Serial.print(",");
  Serial.print(s1);
  Serial.print(",");
  Serial.print(s2);
  Serial.println();
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

boolean filtreTest2(double a){

  if ((a<low2) || (a>high2))
  {
     return true;
  }
  else
  {
    return false;
  }
}


