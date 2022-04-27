#include <Arduino.h>


//déclaration variable

int PIN1=39;
int PIN2=34;
int PIN3=35;
int PIN4=32;


//mesure du capteur a vide
// int const VX1   = analogRead(PIN1);
// int const VX2   = analogRead(PIN2);
// int const VX3   = analogRead(PIN3);
// int const VX4   = analogRead(PIN4);

    
float V1,V2,V3,V4;
float moyv1,moyv2,moyv3,moyv4;
float diffx,diffy;
float moydifx,moydify;

//decla tableaux
unsigned int const nbval=10;
float Val1[nbval],Val2[nbval],Val3[nbval],Val4[nbval];
unsigned int const nbdiff=5;
float tdiffx[nbdiff],tdiffy[nbdiff];



//fonctions

void readVal(){

    for (size_t i = 0; i < nbval-1; i++)
    {
        /* code */
        Val1[i]=Val1[i+1];
        Val2[i]=Val2[i+1];
        Val3[i]=Val3[i+1];
        Val4[i]=Val4[i+1];
    }

    V1   = analogRead(PIN1);
    V2   = analogRead(PIN2);
    V3   = analogRead(PIN3);
    V4   = analogRead(PIN4);

    Val1[nbval-1]=V1;
    Val2[nbval-1]=V2;
    Val3[nbval-1]=V3;
    Val4[nbval-1]=V4;

}

float moyenne(float tab[], unsigned int l){

    int somme=0;
    float m;
    for (size_t i=0 ; i< l ; i++)
    {
        somme += tab[i];
    }
    m = somme / (float)l;
    return m;

}

void moyenneVal(){

    readVal();
    moyv1= moyenne(Val1,nbval);
    moyv2= moyenne(Val2,nbval);
    moyv3= moyenne(Val3,nbval);
    moyv4= moyenne(Val4,nbval);

}

void calculModif(){

    moyenneVal();
    diffx=moyv1+moyv2-moyv3-moyv4;
    diffy=moyv2+moyv4-moyv1-moyv3;
    for (size_t i = 0; i < nbdiff-1; i++)
    {
        tdiffx[i]=tdiffx[i+1];
        tdiffy[i]=tdiffy[i+1];
    }
    tdiffx[nbdiff-1]=diffx;
    tdiffy[nbdiff-1]=diffy;

    moydifx=moyenne(tdiffx,nbdiff);
    moydify=moyenne(tdiffy,nbdiff);

}

String createJson(){
    
    //Mesure les valeurs fait les moyennes et les diff
    calculModif();
    //x
    String JSon = "[{\"x\":";
    JSon+= moydifx;
    JSon+= "},";
    //y
    JSon+="{\"y\":";
    JSon+= moydify;
    JSon+= "}]";
    return JSon;

    
}



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
    pinMode(PIN1, INPUT);
    pinMode(PIN2, INPUT);
    pinMode(PIN3, INPUT);
    pinMode(PIN4, INPUT);

}


void loop() {



    //affichage en Json
    Serial.println(createJson());

    delay(30);
}
