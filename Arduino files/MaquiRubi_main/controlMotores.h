#ifndef __controlMotores_h__
#define __controlMotores_h__
#define __modo_normal__
//#define __modo_alto_par__

enum SentidoGiro {Horario=0,AntiHorario=1};
enum Motor {U=0,D,R,L,F,B};

int motorMatrix[6][4]; // 6 motores con 4 pines de control

void keepOn(int motors[][4],enum Motor mantiene);
void motorMatrix_init();
void secuenciaGiros(char cadena[], int tam);
void giro (bool sentido,int pines[]);
void secuenciaGiros(int MotorMatrix[][4],char cadena[],int tam);
extern SentidoGiro getSentidoGiro(char instruccion);
#endif
