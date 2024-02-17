#include "controlMotores.h"

void secuenciaGiros(char cadena[], uint8_t tam)
{
  instruccion_t instrucciones[tam];
  parsear_instrucciones(instrucciones, cadena, tam);
  ejecutar_instrucciones(instrucciones, tam);
}

instruccion_t map_char_to_instruccion(char comando)
{
  switch(comando)
  {
    case 'U':
      return {
        .motor = {
            .IN1 = U_IN1,
            .IN2 = U_IN2,
            .IN3 = U_IN3,
            .IN4 = U_IN4,
            .ENA = U_ENA,
            .ENB = U_ENB,
            .curr_pos = 0
            },
        .sentido = Horario
        };
    case 'D':
      return {
        .motor = {
            .IN1 = D_IN1,
            .IN2 = D_IN2,
            .IN3 = D_IN3,
            .IN4 = D_IN4,
            .ENA = D_ENA,
            .ENB = D_ENB,
            .curr_pos = 0
            },
        .sentido = Horario
        };
    case 'R':
      return {
        .motor = {
            .IN1 = R_IN1,
            .IN2 = R_IN2,
            .IN3 = R_IN3,
            .IN4 = R_IN4,
            .ENA = R_ENA,
            .ENB = R_ENB,
            .curr_pos = 0
            },
        .sentido = Horario
        };
    case 'L':
      return {
        .motor = {
            .IN1 = L_IN1,
            .IN2 = L_IN2,
            .IN3 = L_IN3,
            .IN4 = L_IN4,
            .ENA = L_ENA,
            .ENB = L_ENB,
            .curr_pos = 0
            },
        .sentido = Horario
        };
    case 'F':
      return {
        .motor = {
            .IN1 = F_IN1,
            .IN2 = F_IN2,
            .IN3 = F_IN3,
            .IN4 = F_IN4,
            .ENA = F_ENA,
            .ENB = F_ENB,
            .curr_pos = 0
            },
        .sentido = Horario
        };
    case 'B':
      return {
        .motor = {
            .IN1 = B_IN1,
            .IN2 = B_IN2,
            .IN3 = B_IN3,
            .IN4 = B_IN4,
            .ENA = B_ENA,
            .ENB = B_ENB,
            .curr_pos = 0
            },
        .sentido = Horario
        };
    case 'u':
      return {
        .motor = {
            .IN1 = U_IN1,
            .IN2 = U_IN2,
            .IN3 = U_IN3,
            .IN4 = U_IN4,
            .ENA = U_ENA,
            .ENB = U_ENB,
            .curr_pos = 0
            },
        .sentido = AntiHorario
        };
    case 'd':
      return {
        .motor = {
            .IN1 = D_IN1,
            .IN2 = D_IN2,
            .IN3 = D_IN3,
            .IN4 = D_IN4,
            .ENA = D_ENA,
            .ENB = D_ENB,
            .curr_pos = 0
            },
        .sentido = AntiHorario
        };
    case 'r':
      return {
        .motor = {
            .IN1 = R_IN1,
            .IN2 = R_IN2,
            .IN3 = R_IN3,
            .IN4 = R_IN4,
            .ENA = R_ENA,
            .ENB = R_ENB,
            .curr_pos = 0
            },
        .sentido = AntiHorario
        };
    case 'l':
      return {
        .motor = {
            .IN1 = L_IN1,
            .IN2 = L_IN2,
            .IN3 = L_IN3,
            .IN4 = L_IN4,
            .ENA = L_ENA,
            .ENB = L_ENB,
            .curr_pos = 0
            },
        .sentido = AntiHorario
        };
    case 'f':
      return {
        .motor = {
            .IN1 = F_IN1,
            .IN2 = F_IN2,
            .IN3 = F_IN3,
            .IN4 = F_IN4,
            .ENA = F_ENA,
            .ENB = F_ENB,
            .curr_pos = 0
            },
        .sentido = AntiHorario
        };
    case 'b':
      return {
        .motor = {
            .IN1 = B_IN1,
            .IN2 = B_IN2,
            .IN3 = B_IN3,
            .IN4 = B_IN4,
            .ENA = B_ENA,
            .ENB = B_ENB,
            .curr_pos = 0
            },
        .sentido = AntiHorario
        };
    default:
      return {
        .motor = {
            .IN1 = 0,
            .IN2 = 0,
            .IN3 = 0,
            .IN4 = 0,
            .ENA = 0,
            .ENB = 0,
            .curr_pos = 0
            },
        .sentido = Stop
        }; //POR QUÉ TENGO QUE HACER ESTO ASÍ? QUIERO PROGRAMARLO EN RUST
      //QUE ALGUIEN ME DE UN Option<T> POR FAVOR
      //MUERTE A LOS NULL!
  }
}

int8_t parsear_instrucciones(instruccion_t instrucciones[], char cadena[], uint8_t tam)
{
    for (uint8_t i = 0; i < tam; i++)
    {
        instrucciones[i] = map_char_to_instruccion(cadena[i]);
        if(instrucciones[i].sentido == Stop)
        {
            return 0;
        }
    }
    return -1;
}

void ejecutar_instrucciones(instruccion_t instrucciones[], uint8_t tam)
{
    for (uint8_t i = 0; i < tam; i++)
    {
        if(instrucciones[i].sentido == Stop)
        {
            return;
        }
        mover_motor_90(instrucciones[i]);
    }
}

void mover_motor_90(instruccion_t instruccion)
{
    static bool pasos[4][4] = {
        {1, 0, 1, 0},
        {1, 0, 0, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}  
    };
    constexpr uint16_t periodo = 60000000.0/(RPM*200.0);

    for(uint8_t i = 0; i < 50; i++)
    {
        if(instruccion.sentido == Horario)
        {
            instruccion.motor.curr_pos++;   
        }
        else
        {
            instruccion.motor.curr_pos--;
        }
        instruccion.motor.curr_pos &= 0b00000011;

        digitalWrite(instruccion.motor.IN1, pasos[instruccion.motor.curr_pos][0]);
        digitalWrite(instruccion.motor.IN2, pasos[instruccion.motor.curr_pos][1]);
        digitalWrite(instruccion.motor.IN3, pasos[instruccion.motor.curr_pos][2]);
        digitalWrite(instruccion.motor.IN4, pasos[instruccion.motor.curr_pos][3]);

        delayMicroseconds(periodo);
    }
}

//Control de corriente
//U
ISR(INT0_vect){
    OCR0A = TCNT0;
}
ISR(INT1_vect){
    OCR0B = TCNT0;
}
//TIMER0_OVF_vect está ocupado por Arduino.h para actualizar millis().
//Probablemente prescinda de la Arduino.h en futuras versiones
ISR(TIMER0_COMPA_vect){
    OCR0A++;
}
ISR(TIMER0_COMPB_vect){
    OCR0B++;
}

//D
ISR(INT2_vect){
    OCR1A = TCNT1;
}
ISR(INT3_vect){
    OCR1B = TCNT1;
}
ISR(TIMER1_OVF_vect){
    OCR1A++;
    OCR1B++;
}

//R
ISR(INT5_vect){
    OCR2A = TCNT2;
}
ISR(PCINT1_vect){
    OCR2B = TCNT1;
}
ISR(TIMER2_OVF_vect){
    OCR2A++;
    OCR2B++;
}

//L, F, B
ISR(PCINT2_vect){
    if(PINK & 0b00000001){
        OCR3A = TCNT3;
    }
    if(PINK & 0b00000010){
        OCR3B = TCNT3;
    }
    if(PINK & 0b00000100){
        OCR4A = TCNT4;
    }
    if(PINK & 0b00001000){
        OCR4B = TCNT4;
    }
    if(PINK & 0b00010000){
        OCR5A = TCNT5;
    }
    if(PINK & 0b00100000){
        OCR5B = TCNT5;
    }
}
//L
ISR(TIMER3_OVF_vect){
    OCR3A++;
    OCR3B++;
}
//F
ISR(TIMER4_OVF_vect){
    OCR4A++;
    OCR4B++;
}
//B
ISR(TIMER5_OVF_vect){
    OCR5A++;
    OCR5B++;
}
