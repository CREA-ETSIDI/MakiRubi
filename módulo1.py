import ComunicacionArduino as ComArd
from time import sleep
import random as rd


def generador():
    string=str()
    for i in range(0,30,1):
        valor=rd.randint(0,25)
        string = string + chr(ord('a')+valor)
    print('The String generated is:   ' + string)
    return string

def movesGenerator(NoMoves):
    string=str()
    for i in range(0,NoMoves,1):
        value=rd.randint(0,5)
        if value==0:    c='F'
        elif value==1:  c='B'
        elif value==2:  c='U'
        elif value==3:  c='D'
        elif value==4:  c='R'
        elif value==5:  c='L'
        else:   c='E'
        up=rd.randint(0,1)
        if up==0:   c+='_'

        string+=c
    print('the moves are:  '+string)
    return string

## Aquí

print('generando secuencia')
cadena=generador()
mov=movesGenerator(20)

a = ComArd.ArduinoCom("COM4",9600)
sleep(2)
print('Enviando cadena')
#a.write(cadena)
sleep(5)
print('Enviando movimientos')
#a.write(mov)

op=input('''
* Introduce la secuencia *
*            o           ^
*       un carácter  
*      x para salir      *
''')
while op!='x' and op!='\t':
    a.write(op)
    if op.upper()=='RECIBIR':
        sleep(1)
        print(a.read())
    else:
        a.write(op)
    op=input("Escriba siguiente secuencia: ")
    
a.Close()



