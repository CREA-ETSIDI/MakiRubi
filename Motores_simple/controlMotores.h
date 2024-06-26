#ifndef __controlMotores_h__
#define __controlMotores_h__

#define MESSAGE_LENGTH 100
#define DEMORA 1000//Aumentamos el delay para evitar sobre calentamientos
#define PASOS 110
#define PASOSUP 110
  //150 con d


#define __modo_normal__
//#define __modo_alto_par__

//enum SentidoGiro {Horario=0,AntiHorario=1};
enum Motor {U=0,D,R,L,F,B};
enum SentidoGiro {Horario=0,AntiHorario=1};

extern int motorMatrix[6][4]; // 6 motores con 4 pines de control

//void keepOn(int motors[][4], Motor mantiene);
void motorMatrix_init();
void secuenciaGiros(char cadena[], int tam);
SentidoGiro getSentidoGiro(char instruccion);
void giro (bool sentido,int pines[], int num_pasos);
bool verifyMessage(char *msg);
//void secuenciaGiros(int MotorMatrix[][4],char cadena[],int tam);
#endif
