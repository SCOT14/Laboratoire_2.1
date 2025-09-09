#include <Arduino.h>
#include <bits_manip.h>
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

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 DDRG = B00000111;
 DDRL = B11111100;
 DDRC = B00000000;
}

void ex1_1 (){
  PORTG = B00000111;
  PORTL = B00000000;
  delay(500);
  PORTG = B00000000;
  PORTL = B00000000;
  delay(500);
}

void ex1_2(){
 if(PIND )
}

void loop() {
  // put your main code here, to run repeatedly:
 ex1_1();
}

