#include <String.h>
#define PIN_LED 13
#define MESSAGE_LENGTH 100

int motorMatrix[6][4]; // 6 motores con 4 pines de control

//char mensaje[MESSAGE_LENGTH]="fFbBdDuUlLrR";
char test_mensaje[MESSAGE_LENGTH]="FLDFLDFLDfldFLdfLD";

enum SentidoGiro {Horario=0,AntiHorario=1};

enum Motor {U=0,D,R,L,F,B};
enum State {INICIO=0,FOTOS,IA,ENVIO_DATOS,EJECUTANDO};

void setup() {
  Serial.begin(9600);

  motorMatrix_init();
  
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED,1);
  
  delay(5000);
}

void loop() {
  static int estadoRecepcionDatos=0;
  static enum State estado=FOTOS;
  static enum State estadoAnterior=INICIO;
  static bool unaVez=false; // Manda una vez la frase a imprimir en la pantalla
  static bool recibiendoDatos=false; // vamos a recibir los datos?
  
  digitalWrite(PIN_LED,0);
  secuenciaGiros(test_mensaje, MESSAGE_LENGTH);
  digitalWrite(PIN_LED,1);
  delay(1000);
}

// Recibe una secuencia de movimientos, los trata y ejecuta los movimientos de los motores 
void secuenciaGiros(char cadena[], int tam)
{
  enum SentidoGiro sentido;
  Serial.write("Moviendo Motores\n");
  for(int i = 0; (i < cadena[i]) && (cadena[i] != '\0'); i++)
  {
    sentido = getSentidoGiro(cadena[i]);
    
    switch(cadena[i])
    {
    case 'R': case 'r':
      //keepOn(motorMatrix,R);
      giro(sentido,motorMatrix[R]);
      break;
    case 'L': case 'l':
      //keepOn(motorMatrix,L);
      giro(sentido,motorMatrix[L]);
      break;
    case 'U': case 'u':
      // keepOn(motorMatrix,U);
      giro(sentido,motorMatrix[U]);
      break;
    case 'D': case 'd':
      //keepOn(motorMatrix,D);
      giro(sentido,motorMatrix[D]);
      break;
    case 'F': case 'f':
      //keepOn(motorMatrix,F);
      giro(sentido,motorMatrix[F]);
      break;
    case 'B': case 'b':
      //keepOn(motorMatrix,B);
      giro(sentido,motorMatrix[B]);
      break;
    }
    delay(500);
  }
}

// Mantiene en funcionamiento el motor que se le ha pasado 
// como parámetro, puede ser que pase a ser un entero
// la variable mantiene
void keepOn(int motors[][4],enum Motor mantiene){
  int pin,motor;
  for(motor=0;motor<6;motor++)
  {
    for(pin=0;pin<4;pin++)
    {
      if(motor!=mantiene)
      {
        digitalWrite(motors[motor][pin], 0);
      }
    }
  }
}

// Guardar los datos que llegan por python
int saveData(char message[], int MAX_LENGTH)  // Saves data returning 0 if it didn't receive data, 1 if it did and 2 for error
{
  if(Serial.available())
  {
    for(int i=0;i<MAX_LENGTH;i++)
    {
      message[i]='\0';
    }
    delay(100);// waiting for message
    int it=0;
    while(Serial.available()>0 && it<MAX_LENGTH)
    {
      message[it]=char(Serial.read());
      it++;
    }
    
    if(it==MAX_LENGTH)
    {
      Serial.flush();
      for(int i=0;i<MAX_LENGTH;i++)
      {
        message[i]='\0';
      }
      return 2;
    }
    return 1;
  }
  return 0;
}

void secuenciaGiros(int MotorMatrix[][4],char cadena[],int tam){
  SentidoGiro sentido;
  //Serial.write("Moviendo Motores\n");
  for(int i = 0; i < cadena[i] != '\0'; i++){ 
    sentido = getSentidoGiro(cadena[i]);   
    switch(cadena[i]){
    case 'R': case 'r':
      keepOn(motorMatrix,R);
      giro(sentido,motorMatrix[R]);
      break;
    case 'L': case 'l':
      keepOn(motorMatrix,L);
      giro(sentido,motorMatrix[L]);
      break;
    case 'U': case 'u':
      keepOn(motorMatrix,U);
      giro(sentido,motorMatrix[U]);
      break;
    case 'D': case 'd':
      keepOn(motorMatrix,D);
      giro(sentido,motorMatrix[D]);
      break;
    case 'F': case 'f':
      keepOn(motorMatrix,F);
      giro(sentido,motorMatrix[F]);
      break;
    case 'B': case 'b':
      keepOn(motorMatrix,B);
      giro(sentido,motorMatrix[B]);
      break;
    }
  }
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

void giro (bool sentido,int pines[]){ // funcion para girar solo 90 grados en un sentido u otro
  int demora = 750;
  
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
    for (int i = 0; i < 110; i++)
    {
      digitalWrite(pines[0], micropasos[i%8][0]);
      digitalWrite(pines[1], micropasos[i%8][1]);
      digitalWrite(pines[2], micropasos[i%8][2]);
      digitalWrite(pines[3], micropasos[i%8][3]);
      delayMicroseconds (demora);
    }
  }
  else
  {
    for (int i = 0; i < 110; i--)
    {
      digitalWrite(pines[3], micropasos[i%8][0]);
      digitalWrite(pines[2], micropasos[i%8][1]);
      digitalWrite(pines[1], micropasos[i%8][2]);
      digitalWrite(pines[0], micropasos[i%8][3]);
      delayMicroseconds (demora);
    }
  }
}
