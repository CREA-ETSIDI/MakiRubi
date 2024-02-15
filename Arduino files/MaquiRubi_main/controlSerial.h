#ifndef __controlSerial_h__
#define __controlSerial_h__
#include <Arduino.h>

#define MESSAGE_LENGTH 100

extern char mensaje[MESSAGE_LENGTH];
extern char test_mensaje[MESSAGE_LENGTH];

enum State {INICIO=0,FOTOS,IA,ENVIO_DATOS,EJECUTANDO};

void getMensaje(char* msg);
int saveData(char message[], int MAX_LENGTH);
void clearData(char data[], int max_len);
char readByte(unsigned long int timeout = 1000);
bool esValido(char caracter);

#endif
