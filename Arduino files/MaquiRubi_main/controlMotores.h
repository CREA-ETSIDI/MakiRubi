#ifndef __controlMotores_h__
#define __controlMotores_h__

#include <Arduino.h>
#include "controlSerial.h"

#define RPM 350

/*********************
***PIN**DEFINITIONS*** 
*********************/
#define U_IN1 0
#define U_IN2 0
#define U_IN3 0
#define U_IN4 0
#define U_ENA 13
#define U_ENB 4
#define U_CMPA 21
#define U_CMPB 20

#define D_IN1 0
#define D_IN2 0
#define D_IN3 0
#define D_IN4 0
#define D_ENA 11
#define D_ENB 12
#define D_CMPA 19
#define D_CMPB 18

#define R_IN1 0
#define R_IN2 0
#define R_IN3 0
#define R_IN4 0
#define R_ENA 10
#define R_ENB 9
#define R_CMPA 3
#define R_CMPB 15

#define L_IN1 0
#define L_IN2 0
#define L_IN3 0
#define L_IN4 0
#define L_ENA 5
#define L_ENB 2
#define L_CMPA 62
#define L_CMPB 63

#define F_IN1 0
#define F_IN2 0
#define F_IN3 0
#define F_IN4 0
#define F_ENA 6
#define F_ENB 7
#define F_CMPA 64
#define F_CMPB 65

#define B_IN1 0
#define B_IN2 0
#define B_IN3 0
#define B_IN4 0
#define B_ENA 46
#define B_ENB 45
#define B_CMPA 66
#define B_CMPB 67

enum sentidogiro_t {Horario, AntiHorario, Stop};

typedef struct{
    uint8_t IN1;
    uint8_t IN2;
    uint8_t IN3;
    uint8_t IN4;
    uint8_t ENA;
    uint8_t ENB;
    uint8_t curr_pos;
} motor_t;

typedef struct{
  motor_t motor;
  sentidogiro_t sentido;
} instruccion_t;

void motor_matrix_setup();
void secuenciaGiros(char cadena[], uint8_t tam);
instruccion_t map_char_to_instruccion(char comando);
int8_t parsear_instrucciones(instruccion_t instrucciones[], char cadena[], uint8_t tam);
void ejecutar_instrucciones(instruccion_t instrucciones[], uint8_t tam);
void mover_motor_90(instruccion_t instruccion);
#endif
