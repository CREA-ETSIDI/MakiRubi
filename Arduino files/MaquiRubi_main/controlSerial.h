#ifndef __controlSerial_h__
#define __controlSerial_h__

#include <Arduino.h>

#define MESSAGE_LENGTH 100

// Guarda en message la secuencia de instrucciones enviada desde python
// max_len es el tamaño máximo de message
// Devuelve 0 en caso de lectura exitosa
// Devuelve -1 en caso de no recibir datos
// Devuelve -2 en caso de que la secuencia recibida sea más larga que max_len y borra los contenidos de message
int saveData(char message[], int MAX_LENGTH);

//Vacía el contenido del array data de longitud max_len
void clearData(char data[], int max_len);

//Lee un caracter del puerto serie
//En caso exitoso devuelve el caracter
//En caso de recibir un caracter invñalido devuelve -1
//En caso de que caduque el timeout devuelve -2
char readByte(unsigned long int timeout = 1000);

//Comprueba si el caracter no pertenece a la tabla ASCII extendida.
//Solo son válidos caractereres de la tabla ASCII no extendida
bool esValido(char caracter);

#endif
