//ensemble des define et des librairies
#include <Arduino.h>
#include <bits_manip.h>
#include <MOMO_RGB_Matrix.h>
#define DEL1R PG2
#define DEL2R PL7
#define DEL3R PL4
#define DEL1G PG1
#define DEL2G PL6
#define DEL3G PL3
#define DEL1B PG0
#define DEL2B PL5
#define DEL3B PL2
#define BTN PC2


MOMO_RGB_Matrix matrix; //création de la matrice
const unsigned long temps_remp_rinc = 5000;
const unsigned long clignote_lent = 500;
const unsigned long clignote_vite = 250;

//Machine à état
enum Etat {
  Attente,
  Remplissage,
  Lavage,
  Rincage,
  Essorage, 
  Fin
};



void setup() {
  // 
 Serial.begin(9600); //allumer le port série
 matrix.begin(); //allume la matrice a del
 matrix.setCursor(8, 0); //deplace le curseur au point 8,0
 matrix.setTextColor(matrix.Color333(7,7,7)); //set la couleur des pixels de txt
 matrix.fillScreen(matrix.Color333(0, 0, 0)); // remplis l'écran de noir 
 DDRG = B00000111; 
 DDRL = B11111100;  //configuration entrée/sorties
 DDRC = B00000000;
 PORTC = B11111111; //active input pullup
}



static Etat etat = Attente; 

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long currentMillis = millis();
 static unsigned long etatStart = 0; 
 if(PINC == B00000010){ //on effectue un arrêt si le bouton 2 est appuyer
  etat = Attente; 
 }
  switch(etat){
    case Attente:
      matrix.fillScreen(matrix.Color333(0, 0, 0));  //noir
      Serial.println("ARRET");  //affiche ARRET sur le port série
      matrix.print("ARRET");    //affiche ARRET sur la matrice
      if(PINC == B00000001) //si le bouton 1 est appuyer
      etat = Remplissage; //change l'état de la machine
      break;

    case Remplissage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("REMPLISSAGE");
      Serial.println("REMPLISSAGE");
      analogWrite(PG1, 255); //allume une del en vert 
      if(currentMillis - etatStart >= temps_remp_rinc){ //si le temps depasse 5000
        analogWrite(PG1, 0); //on éteint la del
        etatStart = currentMillis; //stock la variable
      }
      etat = Lavage;    //changement d'état
      break;

    case Lavage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("LAVAGE");
      Serial.println("LAVAGE");
      for(int i = 0; i < 10; i++){
        PORTG = flipBit(PORTG, PG0);
        delay(500);
      }
      etat = Rincage;   //changement d'état
      break;
    
    case Rincage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("RINCAGE");
      Serial.println("RINCAGE");
      analogWrite(PG2, 255);    //allume une del en rouge
      if(currentMillis - etatStart >=temps_remp_rinc){
        analogWrite(PG2, 0);    //éteint la del
        etatStart = currentMillis;
      }
      etat = Essorage;    //changement d'état
      break;

    case Essorage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("ESSORAGE");
      Serial.println("ESSORAGE");
      for(int i = 0; i < 20; i++){
        PORTG = flipBit(PORTG, PG1);
        delay(250);
      }
      
      etat = Fin; //changement d'état
      break;
    
    case Fin:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("FIN CYCLE");
      Serial.println("FIN DU CYCLE");
      delay(1000);
      etat = Attente; //retour au départ
      break;

  }
}

