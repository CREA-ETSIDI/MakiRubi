#include "controlSerial.h"

// Guardar los datos que llegan por python
int saveData(char message[], int max_len)  // Saves data returning 0 if it didn't receive data, 1 if it did and 2 for error
{
    if(!Serial.available())
    {
        return 0;
    }

    clearData(message, max_len);

    delay(100);// waiting for message
    for(int i = 0; i < max_len; i++)
    {
        message[i]=char(Serial.read());
        if(message[i] == '\n')
        {
          return 1;
        }
    }

    Serial.flush();
    clearData(message, max_len);
    return 2;
}

void clearData(char data[], int max_len)
{

    for(int i=0;i<max_len;i++)
    {
        data[i]='\0';
    }
}

//Devuelve el caracter recibido o -1 en caso de error
char readByte(unsigned long int timeout = 1000)
{
    unsigned long int end_time = millis() + timeout;
    while(millis() < end_time)
    {
        if(Serial.available())
        {
            char caracter = Serial.read();
            return caracter;
        }
    }
    return -1;
}

//Comprueba si el caracter no pertenece a la tabla ASCII extendida.
//Solo son válidos caractereres de la tabla ASCII no extendida
bool esValido(char caracter)
{
    return caracter & 0b10000000;
}
