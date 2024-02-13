#include "controlSerial.h"

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
