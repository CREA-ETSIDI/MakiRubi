#include "controlMotores.h"

void secuenciaGiros(char cadena[], int tam)
{
  
}

instruccion map_char_to_instruccion(char comando)
{
  switch(comando)
  {
    case 'U':
      return {U, Horario};
    case 'D':
      return {D, Horario};
    case 'R':
      return {R, Horario};
    case 'L':
      return {L, Horario};
    case 'F':
      return {F, Horario};
    case 'B':
      return {B, Horario};
    case 'u':
      return {U, AntiHorario};
    case 'd':
      return {D, AntiHorario};
    case 'r':
      return {R, AntiHorario};
    case 'l':
      return {L, AntiHorario};
    case 'f':
      return {F, AntiHorario};
    case 'b':
      return {B, AntiHorario};
    default:
      return {Null, Horario}; //POR QUÉ TENGO QUE HACER ESTO ASÍ? QUIERO PROGRAMARLO EN RUST
      //QUE ALGUIEN ME DE UN Option<T> POR FAVOR
      //MUERTE A LOS NULL!
  }
}
