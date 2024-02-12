#include <String.h>
#define PIN_LED 13
#define MESSAGE_LENGTH 100

char mensaje[MESSAGE_LENGTH];
char test_mensaje[MESSAGE_LENGTH]="FLDFLDFLDfldFLdfLD";

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

  getMensaje(mensaje);
  
  digitalWrite(PIN_LED,0);
  secuenciaGiros(mensaje, MESSAGE_LENGTH);
  digitalWrite(PIN_LED,1);
  delay(1000);
}

// Recibe una secuencia de movimientos, los trata y ejecuta los movimientos de los motores 

void getMensaje(char* msg){
  unsigned int i = 0;
  char lastChar = 255;
  while(lastChar != '\n' && i < MESSAGE_LENGTH){
    if (Serial.available() > 0) {
      lastChar = Serial.read();
      Serial.print("I received: ");
      Serial.println(lastChar, DEC);
      msg[i] = lastChar;
      i++;
    }
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
