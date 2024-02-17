#include <String.h>
#include "controlMotores.h"
#include "controlSerial.h"

#define PIN_LED 13

int motorMatrix[6][4]; // 6 motores con 4 pines de control
char mensaje[MESSAGE_LENGTH];
char test_mensaje[MESSAGE_LENGTH]="FLDFLDFLDfldFLdfLD";

void setup() {
    motor_matrix_setup();
    Serial.begin(9600);
    
    pinMode(PIN_LED,OUTPUT);
    digitalWrite(PIN_LED,1);
    
    delay(5000);
}

void loop() {
    saveData(mensaje, MESSAGE_LENGTH);
    
    digitalWrite(PIN_LED,0);
    secuenciaGiros(mensaje, MESSAGE_LENGTH);
    digitalWrite(PIN_LED,1);
    
    delay(1000);
}
