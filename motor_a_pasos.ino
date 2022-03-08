int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;

int motorR[]={10,11,12,13};
int motorL[]={};
int motorU[]={};
int motorD[]={};
int motorF[]={};
int motorB[]={};
// Por comodidad al escribir el código y aumentar su 
// reutilización, se considera el usar una matriz
int motorMatrix[6][4]; // 6 motores con 4 pines de control

// Falta saber para que valores que se pasan a la función giro
// el giro efectuado por el motor es horario o antihorario
enum SentidoGiro {Horario=0,AntiHorario};

// Esto permite de una manera sencilla controlar los motores, también se pueden usar MACROS
enum Motor {U=0,D,R,L,F,B};


void setup() {
  
  int i;
  
  for(i=0;i<4;i++){
    motorMatrix[R][i]=10+i;
    pinMode (motorR[i], OUTPUT);
  }
  /*
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);*/
}

void loop() {
  
  giro (1,motorR);
  delay(1000);
  giro (0,motorR);
  delay(1000);
  giro (0,motorR);
  delay(1000);
  /*
  giro (1);
  delay(1000);
  giro (0);
  delay(1000);
  giro (0);
  delay(1000);*/
}


// Esta función ha sido modificada respecto a la original, 
// usando variables locales y paso por referencia
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

  if (sentido == 0){
    for (int i = 0; i < 100; i++){
        digitalWrite(pines[0], micropasos[i%8][0]);
        digitalWrite(pines[1], micropasos[i%8][1]);
        digitalWrite(pines[2], micropasos[i%8][2]);
        digitalWrite(pines[3], micropasos[i%8][3]);
        delayMicroseconds (demora);
    }
  }
  else{
    for (int i = 0; i < 100; i++){
        digitalWrite(pines[3], micropasos[i%8][0]);
        digitalWrite(pines[2], micropasos[i%8][1]);
        digitalWrite(pines[1], micropasos[i%8][2]);
        digitalWrite(pines[0], micropasos[i%8][3]);
        delayMicroseconds (demora);
    }
  }
}


// Recibe una secuencia de movimientos, los trata y ejecuta los movimientos de los motores 
void secuenciaGiros(String cadena, int tam) {

   int i;
   enum SentidoGiro sentido;

   // Va caracter por caracter ejecutando la instrucción
   for(i=0;i<cadena.length()-1;i++){

      // Distingue sí el sentido de giro es horario o antihorario
      if(cadena[i]>='a' && cadena[i]<='z')  sentido = AntiHorario;  
      else if (cadena[i]>='A' && cadena[i] <= 'Z') sentido = Horario;

      // Switch para la ejecución de un giro, 
      // apagando del resto de señales de control de los motores
      switch(cadena[i]){
        case 'R': case 'r':
          keepOn(motorMatrix,R);
          giro(sentido,motorMatrix[R]);
          break;
        case 'L': case 'l':
          keepOn(motorMatrix,L);
          giro(sentido,motorMatrix[L]); break;
        case 'U': case 'u':
          keepOn(motorMatrix,U);
          giro(sentido,motorMatrix[U]); break;
        case 'D': case 'd':
          keepOn(motorMatrix,D);
          giro(sentido,motorMatrix[D]); break;
        case 'F': case 'f':
          keepOn(motorMatrix,F);
          giro(sentido,motorMatrix[F]); break;
        case 'B': case 'b':
          keepOn(motorMatrix,B);
          giro(sentido,motorMatrix[B]); break;
        };
        
    }
    
}

// Mantiene en funcionamiento el motor que se le ha pasado 
// como parámetro, puede ser que pase a ser un entero
// la variable mantiene
void keepOn(int motors[][4],enum Motor mantiene){
    int pin,motor;
    for(motor=0;motor<6;motor++){
      for(pin=0;pin<4;pin++){
        if(motor!=mantiene){
          digitalWrite(motors[motor][pin],0);
          }
        }
      }
}
