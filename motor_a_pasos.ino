int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
enum SentidoGiro {Horario,AntiHorario};
void setup() {
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
}

void loop() {
  giro (1);
  delay(1000);
  giro (0);
  delay(1000);
  giro (0);
  delay(1000);
}

void giro (bool sentido){ // funcion para girar solo 90 grados en un sentido u otro
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
        digitalWrite(IN1, micropasos[i%8][0]);
        digitalWrite(IN2, micropasos[i%8][1]);
        digitalWrite(IN3, micropasos[i%8][2]);
        digitalWrite(IN4, micropasos[i%8][3]);
        delayMicroseconds (demora);
    }
  }
  else{
    for (int i = 0; i < 100; i++){
        digitalWrite(IN4, micropasos[i%8][0]);
        digitalWrite(IN3, micropasos[i%8][1]);
        digitalWrite(IN2, micropasos[i%8][2]);
        digitalWrite(IN1, micropasos[i%8][3]);
        delayMicroseconds (demora);
    }
  }
}

void giro(enum SentidoGiro sentido) {
    if (sentido==Horario) {
        giro(0);
    }
    else {
        giro(1);
    }
}
