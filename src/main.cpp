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

MOMO_RGB_Matrix matrix;
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
 Serial.begin(9600);
 matrix.begin();
 matrix.setCursor(8, 0);
 matrix.setTextColor(matrix.Color333(7,7,7));
 matrix.fillScreen(matrix.Color333(0, 0, 0));
 DDRG = B00000111; 
 DDRL = B11111100;
 DDRC = B00000000;
 PORTC = B11111111; //active input pullup
}





void loop() {
  // put your main code here, to run repeatedly:
 Etat etat = Attente;
 unsigned long currentMillis = millis();
 static unsigned long etatStart = 0; 

  switch(etat){
    case Attente:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      Serial.println("ARRET");
      matrix.print("ARRET");
      if(PINC = B00000001) //si le bouton est appuyer
      etat = Remplissage;
      break;

    case Remplissage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("REMPLISSAGE");
      Serial.println("REMPLISSAGE");
      PORTG = B00000010; //allume une del en vert 
      if(currentMillis - etatStart >= temps_remp_rinc){
        PORTG = B00000000;
        etatStart = currentMillis;
      }
      etat = Lavage;
      break;

    case Lavage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("LAVAGE");
      Serial.println("LAVAGE");
      for(int i = 0; i < 10; i++){
        PORTL = B10000000;
        if(currentMillis - etatStart >= clignote_lent){
          PORTL = B00000000;
          etatStart = currentMillis;
        }
      }
      etat = Rincage;
      break;
    
    case Rincage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("RINCAGE");
      Serial.println("RINCAGE");
      PORTL = B00000100;
      if(currentMillis - etatStart >=temps_remp_rinc){
        PORTL = B00000000;
        etatStart = currentMillis;
      }
      etat = Essorage;
      break;

    case Essorage:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("ESSORAGE");
      Serial.println("ESSORAGE");
      for(int i = 0; i < 20; i++){
        PORTL = B00000100;
        if(currentMillis - etatStart >= clignote_vite){
          PORTL = B00000000;
          etatStart = currentMillis;
        }
      }
      etat = Fin;
      break;
    
    case Fin:
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.print("FIN CYCLE");
      Serial.println("FIN DU CYCLE");
      delay(1000);
      etat = Attente;
      break;

  }
}

