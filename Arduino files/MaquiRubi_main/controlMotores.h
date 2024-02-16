#ifndef __controlMotores_h__
#define __controlMotores_h__

#define __modo_normal__
//#define __modo_alto_par__

enum motor_t {U, D, R, L, F, B};
enum sentidogiro_t {Horario, AntiHorario};
void secuenciaGiros(char cadena[], int tam);
#endif
