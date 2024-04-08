#include <String.h>
#include "controlMotores.h"

#define PIN_LED 13

int flag = 0;
int motorMatrix[6][4]; // 6 motores con 4 pines de control
char mensaje[MESSAGE_LENGTH]= "UDFLBR";
char test_mensaje[MESSAGE_LENGTH]="FLDFLDFLDfldFLdfLD";

void setup() {
  Serial.begin(9600);

  motorMatrix_init();
  
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED,1);
  
  delay(5000);
}

void loop() {
  Serial.print("HOLA");
  if (flag == 0){
    digitalWrite(PIN_LED,0);
    secuenciaGiros(mensaje, MESSAGE_LENGTH);
    flag = 1;
    digitalWrite(PIN_LED,1);
  }
  delay(1000);
}
