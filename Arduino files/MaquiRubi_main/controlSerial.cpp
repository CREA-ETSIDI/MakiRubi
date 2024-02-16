#include "controlSerial.h"

// Guarda en message la secuencia de instrucciones enviada desde python
// max_len es el tamaño máximo de message
// Devuelve 0 en caso de lectura exitosa
// Devuelve -1 en caso de no recibir datos
// Devuelve -2 en caso de que la secuencia recibida sea más larga que max_len y borra los contenidos de message
int saveData(char message[], int max_len)
{
    if(!Serial.available())
    {
        return 0;
    }

    clearData(message, max_len);

    delay(100);// waiting for message
    for(int i = 0; i < max_len; i++)
    {
        message[i]= readByte();
        if(message[i] == '\n')
        {
          return 1;
        }
    }

    Serial.flush();
    clearData(message, max_len);
    return 2;
}

//Vacía el contenido del array data de longitud max_len
void clearData(char data[], int max_len)
{
    for(int i=0;i<max_len;i++)
    {
        data[i]='\0';
    }
}

//Lee un caracter del puerto serie
//En caso exitoso devuelve el caracter
//En caso de recibir un caracter invñalido devuelve -1
//En caso de que caduque el timeout devuelve -2
char readByte(unsigned long int timeout = 1000)
{
    unsigned long int end_time = millis() + timeout;
    while(millis() < end_time)
    {
        if(Serial.available())
        {
            char caracter = Serial.read();

            if (esValido(caracter))
            {
              return caracter; 
            }
            else
            {
              return -1;
            }
        }
    }
    return -2; //POR QUÉ TENGO QUE HACER ESTO ASÍ? QUIERO PROGRAMARLO EN RUST
    //QUE ALGUIEN ME DE UN Result<T> POR FAVOR
}

//Comprueba si el caracter no pertenece a la tabla ASCII extendida.
//Solo son válidos caractereres de la tabla ASCII no extendida
bool esValido(char caracter)
{
    return caracter & 0b10000000;
}
