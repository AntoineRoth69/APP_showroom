#include <Arduino.h>

//coefficient des bornes par rapport valeur max
//borne large
#define coeffH 0.75
#define coeffL 0.25
//dection pic
#define coeffH2 0.90
//borne fine
#define coeffH3 0.55
#define coeffL3 0.45


//alim en 3,3V
//pin d'entrée
int PIN1=A0;
int PIN2=A1;
int PIN3=A2;
int PIN4=A3;
int PIN5=A4;


int x_max=0;


//init read
double x1;
double x2;
double x3;
double x4;
double x5;

//init resultats
int val_max;
int s1,s2,s3,s4,s5;


//fontion decla
boolean filtreTest(double a, int x_max);
boolean filtreTest2(double a, int x_max);
boolean filtreTest3(double a, int x_max);
int resultG(double x, int g);
int valmax(double x);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN1, INPUT);
  pinMode(PIN2, INPUT);
  pinMode(PIN3, INPUT);
  pinMode(PIN4, INPUT);
  pinMode(PIN5, INPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
  
  //lecture 
  x1=analogRead(PIN1);
  x2=analogRead(PIN2);
  x3=analogRead(PIN3);
  x4=analogRead(PIN4);
  x5=analogRead(PIN5);


  /*
  val_max= valmax(x1);

  
  //resultats avec gain et filtre
  s1=resultG(x1,1);
  s2=resultG(x1,2);
  s3=resultG(x1,3);


  //affichage
  Serial.print(x1);
  Serial.print(",");

  Serial.print(val_max);
  Serial.print(",");

  Serial.print(s1);
  Serial.print(",");

  Serial.print(s2);
  Serial.print(",");

  Serial.print(s3);
  Serial.println();
*/
  

  //mais oui le json

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


  Serial.println(JSonString);

  delay(1000);

}

//fonctions
boolean filtreTest(double a, int x_max){

  int high= int(coeffH*x_max);
  int low= int(coeffL*x_max);

  if ((a<low) || (a>high))
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean filtreTest2(double a, int x_max){

  int high2= int(coeffH2*x_max);
  if ((a<0) || (a>high2))
  {
     return true;
  }
  else
  {
    return false;
  }
}

boolean filtreTest3(double a, int x_max){
  
  int high3= int(coeffH3*x_max);
  int low3= int(coeffL3*x_max);

  if ((a<low3) || (a>high3))
  {
     return true;
  }
  else
  {
    return false;
  }
}


int resultG(double x, int g){

  if (g==1)
  {
    return coeffH*val_max*filtreTest(x, val_max);
  }
  
  if (g==2)
  {
    return coeffH2*val_max*filtreTest2(x, val_max);
  }
  
    if (g==3)
  {
    return coeffH3*val_max*filtreTest3(x, val_max);
  }
  return false;
}

int valmax(double x){

  if (x > x_max)
  {
    x_max=x;
  }
  return x_max;
}

 