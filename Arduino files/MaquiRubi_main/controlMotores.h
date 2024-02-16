#ifndef __controlMotores_h__
#define __controlMotores_h__

#include <Arduino.h>
#include "controlSerial.h"

#define __modo_normal__
//#define __modo_alto_par__

enum motor_t {Null, U, D, R, L, F, B};
enum sentidogiro_t {Horario, AntiHorario};

typedef struct{
  motor_t motor;
  sentidogiro_t sentido;
} instruccion;

void secuenciaGiros(char cadena[], int tam);
instruccion map_char_to_instruccion(char comando);
int parsear_instrucciones(instruccion instrucciones[], char cadena[], int tam);
#endif
