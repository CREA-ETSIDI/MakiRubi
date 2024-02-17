#include "controlMotores.h"

void motor_matrix_setup()
{
    //Pines de control de los motores
    pinMode(U_IN1, OUTPUT);
    pinMode(U_IN2, OUTPUT);
    pinMode(U_IN3, OUTPUT);
    pinMode(U_IN4, OUTPUT);
    pinMode(U_ENA, OUTPUT);
    pinMode(U_ENB, OUTPUT);
    pinMode(U_CMPA, INPUT);
    pinMode(U_CMPB, INPUT);
    
    pinMode(D_IN1, OUTPUT);
    pinMode(D_IN2, OUTPUT);
    pinMode(D_IN3, OUTPUT);
    pinMode(D_IN4, OUTPUT);
    pinMode(D_ENA, OUTPUT);
    pinMode(D_ENB, OUTPUT);
    pinMode(D_CMPA, INPUT);
    pinMode(D_CMPB, INPUT);
    
    pinMode(R_IN1, OUTPUT);
    pinMode(R_IN2, OUTPUT);
    pinMode(R_IN3, OUTPUT);
    pinMode(R_IN4, OUTPUT);
    pinMode(R_ENA, OUTPUT);
    pinMode(R_ENB, OUTPUT);
    pinMode(R_CMPA, INPUT);
    pinMode(R_CMPB, INPUT);
    
    pinMode(L_IN1, OUTPUT);
    pinMode(L_IN2, OUTPUT);
    pinMode(L_IN3, OUTPUT);
    pinMode(L_IN4, OUTPUT);
    pinMode(L_ENA, OUTPUT);
    pinMode(L_ENB, OUTPUT);
    pinMode(L_CMPA, INPUT);
    pinMode(L_CMPB, INPUT);
    
    pinMode(F_IN1, OUTPUT);
    pinMode(F_IN2, OUTPUT);
    pinMode(F_IN3, OUTPUT);
    pinMode(F_IN4, OUTPUT);
    pinMode(F_ENA, OUTPUT);
    pinMode(F_ENB, OUTPUT);
    pinMode(F_CMPA, INPUT);
    pinMode(F_CMPB, INPUT);
    
    pinMode(B_IN1, OUTPUT);
    pinMode(B_IN2, OUTPUT);
    pinMode(B_IN3, OUTPUT);
    pinMode(B_IN4, OUTPUT);
    pinMode(B_ENA, OUTPUT);
    pinMode(B_ENB, OUTPUT);
    pinMode(B_CMPA, INPUT);
    pinMode(B_CMPB, INPUT);

    cli(); //Deshabilitar interupciones globales no nos la vayan a liar
    //Interrupciones de los temporizadores
    TIMSK0 |= 0b00000110; //Activa las interrupciones TIMER0_COMPA y TIMER0_COMPB
    TIMSK1 |= 0b00000001; //Activa la interrupción TIMER1_OVF
    TIMSK2 |= 0b00000001; //Activa la interrupción TIMER2_OVF
    TIMSK3 |= 0b00000001; //Activa la interrupción TIMER3_OVF
    TIMSK4 |= 0b00000001; //Activa la interrupción TIMER4_OVF
    TIMSK5 |= 0b00000001; //Activa la interrupción TIMER5_OVF

    //Interrupciones externas
    EICRA = 0xFF; //Define las interrupciones externas INT0, INT1, INT2 e INT3, a activarse en el flanco positivo
    EICRB |= 0b00001100; //Define la interrupción externa INT5 a activarse en el flanco positivo
    EIMSK = 0b00101111; //Activa las interrupciones INT0, INT1, INT2, INT3 e INT5

    PCMSK1 = 0b00000001; //Define que solo el pin 15 contribuirá a la interrupción PCINT1
    PCMSK2 = 0b00111111; //Define que solo los pines 62, 63, 64, 65, 66 y 67 contribuirán a la interrupción PCINT2
    PCIFR &= 0b11111000; //↓
    PCIFR |= 0b00000110; //Activa las interrupciones PCINT2 y PCINT1

    //Configuración de PWM en modo inverso (Ya que en estos puentes H ENA y ENB son activos a nivel bajo)
    TCCR0A |= 0b11110000;
    TCCR1A |= 0b11110000;
    TCCR2A |= 0b11110000;
    TCCR3A |= 0b11110000;
    TCCR4A |= 0b11110000;
    TCCR5A |= 0b11110000;

    sei(); //Reactivar interrupciones globales
}

void secuenciaGiros(char cadena[], uint8_t tam)
{
    instruccion_t instrucciones[tam];
    parsear_instrucciones(instrucciones, cadena, tam);
    ejecutar_instrucciones(instrucciones, tam);
}

instruccion_t map_char_to_instruccion(char comando)
{
  switch (comando)
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
        if (instrucciones[i].sentido == Stop)
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
        if (instrucciones[i].sentido == Stop)
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

    for (uint8_t i = 0; i < 50; i++)
    {
        if (instruccion.sentido == Horario)
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
ISR(INT0_vect)
{
    OCR0A = TCNT0;
}
ISR(INT1_vect)
{
    OCR0B = TCNT0;
}
//TIMER0_OVF_vect está ocupado por Arduino.h para actualizar millis().
//Probablemente prescinda de la Arduino.h en futuras versiones
ISR(TIMER0_COMPA_vect)
{
    OCR0A++;
}
ISR(TIMER0_COMPB_vect)
{
    OCR0B++;
}

//D
ISR(INT2_vect)
{
    OCR1A = TCNT1;
}
ISR(INT3_vect)
{
    OCR1B = TCNT1;
}
ISR(TIMER1_OVF_vect)
{
    OCR1A++;
    OCR1B++;
}

//R
ISR(INT5_vect)
{
    OCR2A = TCNT2;
}
ISR(PCINT1_vect)
{
    if (PINJ0 & 0b00000001)
    {
        OCR2B = TCNT1;   
    }
}
ISR(TIMER2_OVF_vect)
{
    OCR2A++;
    OCR2B++;
}

//L, F, B
ISR(PCINT2_vect)
{
    if (PINK & 0b00000001)
    {
        OCR3A = TCNT3;
    }
    if (PINK & 0b00000010)
    {
        OCR3B = TCNT3;
    }
    if (PINK & 0b00000100)
    {
        OCR4A = TCNT4;
    }
    if (PINK & 0b00001000)
    {
        OCR4B = TCNT4;
    }
    if (PINK & 0b00010000)
    {
        OCR5A = TCNT5;
    }
    if (PINK & 0b00100000)
    {
        OCR5B = TCNT5;
    }
}
//L
ISR(TIMER3_OVF_vect)
{
    OCR3A++;
    OCR3B++;
}
//F
ISR(TIMER4_OVF_vect)
{
    OCR4A++;
    OCR4B++;
}
//B
ISR(TIMER5_OVF_vect)
{
    OCR5A++;
    OCR5B++;
}
