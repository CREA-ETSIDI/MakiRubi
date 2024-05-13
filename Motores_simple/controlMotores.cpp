#include "controlMotores.h"
#include <Arduino.h>

//Creo yo que los valores son los pines usados con el motor
bool verifyMessage(char *msg)
{
  int i;
  int flag = 0;
  while (msg[i])
  {
    switch(msg[i])
    {
    case 'R': case 'r':
      flag = 0;
      break;
    case 'L':case 'l':
      flag = 0;
      break;
    case 'U':case 'u':
      flag = 0;
      break;
    case 'D': case 'd':
      flag = 0;
      break;
    case 'F': case 'f':
      flag = 0;
      break;
    case 'B':case 'b':
      flag = 0;
      break;
    default:
      flag = 1;
      break;
    }
  } 
  return (flag);
}


void motorMatrix_init(){
  for(int i=0;i<4;i++)
  {
    motorMatrix[U][i]=47+2*i;
    motorMatrix[D][i]=31+2*i;
    motorMatrix[R][i]=30+2*i;
    motorMatrix[L][i]=38+2*i;
    motorMatrix[F][i]=39+2*i;
    motorMatrix[B][i]=46+2*i;
  }
  for(int i=0;i<4;i++)
  { 
    pinMode(motorMatrix[U][i],OUTPUT);
    pinMode(motorMatrix[L][i],OUTPUT);
    pinMode(motorMatrix[D][i],OUTPUT);
    pinMode(motorMatrix[R][i],OUTPUT);
    pinMode(motorMatrix[B][i],OUTPUT);
    pinMode(motorMatrix[F][i],OUTPUT);
  }
  Serial.println("Todo bien inicializado");
}

SentidoGiro getSentidoGiro(char instruccion)
{
  if(instruccion >= 'a' && instruccion <= 'z'){
    return AntiHorario;  
  }
  else{
    return Horario;
  }
}

void secuenciaGiros(char cadena[], int tam)
{
  enum SentidoGiro sentido;
  Serial.write("Moviendo Motores\n");
  for(int i = 0; cadena[i] != '\0'; i++)
  {
    Serial.print(i);Serial.print(": ");
    Serial.println(cadena[i]);
    sentido = getSentidoGiro(cadena[i]);

    Serial.println(sentido);
    switch(cadena[i])
    {
    case 'r': 
      giro(Horario,motorMatrix[R], 110);
      break;
    case 'R':
      giro(AntiHorario,motorMatrix[R], 100);
      break;
    case 'l':
      giro(Horario,motorMatrix[L], 102);
      break;
    case 'L':
      giro(AntiHorario,motorMatrix[L], 102);
      break;
    case 'u':
      giro(Horario,motorMatrix[U], 102);
      break;
    case 'U':
      giro(AntiHorario,motorMatrix[U], 102);
      break;
    case 'd':
      giro(Horario,motorMatrix[D], 102);
      break;
    case 'D':
      giro(AntiHorario,motorMatrix[D], 102);
      break;
    case 'f':
      giro(Horario,motorMatrix[F], 102);
      break;
    case 'F':
      giro(AntiHorario,motorMatrix[F], 104);
      break;
    case 'b':
      giro(Horario,motorMatrix[B], 106);
      break;
    case 'B':
      giro(AntiHorario,motorMatrix[B], 102);
      break;
    }
    delay(DEMORA);
  }
}
#ifdef __modo_normal__
void giro (bool sentido,int pines[], int num_pasos){ // funcion para girar solo 90 grados en un sentido u otro
  bool micropasos[8][4] = {
    {1, 0, 0, 0},
    {1, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
  };
  
  if (sentido == 0)
  {
    for (int i = 0; i < num_pasos; i++)
    {
      digitalWrite(pines[0], micropasos[i%8][0]);
      digitalWrite(pines[1], micropasos[i%8][1]);
      digitalWrite(pines[2], micropasos[i%8][2]);
      digitalWrite(pines[3], micropasos[i%8][3]);
      delayMicroseconds (DEMORA);
    }
  }
  else
  {
    for (int i = num_pasos; i > 0; i--)
    {
      digitalWrite(pines[0], micropasos[i%8][0]);
      digitalWrite(pines[1], micropasos[i%8][1]);
      digitalWrite(pines[2], micropasos[i%8][2]);
      digitalWrite(pines[3], micropasos[i%8][3]);
      delayMicroseconds (DEMORA);
    }
  }
  digitalWrite(pines[0], 0);
  digitalWrite(pines[1], 0);
  digitalWrite(pines[2], 0);
  digitalWrite(pines[3], 0);

}
#else
#ifdef __modo_alto_par__
void giro (bool sentido,int pines[]){ // funcion para girar solo 90 grados en un sentido u otro
  int DEMORA = 750;
  
  bool micropasos[4][4] = {
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 0, 1}
  };
  
  if (sentido == 0)
  {
    for (int i = 0; i < 50; i++)
    {
      digitalWrite(pines[0], micropasos[i%4][0]);
      digitalWrite(pines[1], micropasos[i%4][1]);
      digitalWrite(pines[2], micropasos[i%4][2]);
      digitalWrite(pines[3], micropasos[i%4][3]);
      delayMicroseconds (DEMORA);
    }
  }
  else
  {
    for (int i = 0; i < 150; i--)
    {
      digitalWrite(pines[3], micropasos[i%4][0]);
      digitalWrite(pines[2], micropasos[i%4][1]);
      digitalWrite(pines[1], micropasos[i%4][2]);
      digitalWrite(pines[0], micropasos[i%4][3]);
      delayMicroseconds (DEMORA);
    }
  }
}
#endif
#endif
