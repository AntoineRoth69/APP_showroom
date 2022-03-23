#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//coefficient des bornes par rapport valeur max
//borne large
#define coeffH 0.75
#define coeffL 0.25
//dection pic
#define coeffH2 0.90
//borne fine
#define coeffH3 0.55
#define coeffL3 0.45

//temps d'etalonnage en secondes
const int time=10;

//alim en 3,3V
int PIN=A0;
int x_max=0;


//init resultats
double x;
int val_max;
int s1,s2,s3;
LiquidCrystal_I2C lcd(0x27,20,4);

//fontion decla
boolean filtreTest(double a, int x_max);
boolean filtreTest2(double a, int x_max);
boolean filtreTest3(double a, int x_max);
int resultG(double x, int g);
void affichagelcd(double x, int s1, int s2, int s3, LiquidCrystal_I2C lcd);
int valmax(double x);


//int etalon(int time);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN, INPUT);

  //lcd init
  lcd.init();
  lcd.backlight();


  
  //etalonnage des bornes 
  //val_max=etalon(time);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //lecture 
  x=analogRead(PIN);

  val_max= valmax(x);
  //resultats avec gain et filtre
  s1=resultG(x,1);
  s2=resultG(x,2);
  s3=resultG(x,3);


  //affichage
  Serial.print(x);
  Serial.print(",");

  Serial.print(val_max);
  Serial.print(",");

  Serial.print(s1);
  Serial.print(",");

  Serial.print(s2);
  Serial.print(",");

  Serial.print(s3);
  Serial.println();

  affichagelcd(x,s1,s2,s3,lcd);
  
  delay(500);

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

int etalon(int time){

  //init du temps d'etalonnage 
  int delais= 5;
  int compteur=0;
  double x_max=0;
  int fin_compteur= time*1000/delais;

  while (compteur <= fin_compteur)
  {
    x=analogRead(PIN);
    if (x > x_max)
    {
      x_max=x;

    }
    delay(delais);
    compteur++;
  }
  //retour de la valeur max
  return x_max;
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
/*
void affichagelcd(double x, int s1, int s2, int s3, LiquidCrystal_I2C lcd){

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(1,1);

    if (s2!=0)
  {
    lcd.print("grand mouvement");
  }
  else
  {
      if (s1!=0)
    {
      lcd.print("mouvement detecté");
    }
    else
    {
        if (s3!=0)
      {
        lcd.print("petit mouvement");
      }
      else
      {
        lcd.print("personne");
      }
      
    }
    
  }
 
  


}
 */