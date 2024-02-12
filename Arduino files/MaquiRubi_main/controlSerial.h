#define MESSAGE_LENGTH 100


char mensaje[MESSAGE_LENGTH];
char test_mensaje[MESSAGE_LENGTH]="FLDFLDFLDfldFLdfLD";

enum State {INICIO=0,FOTOS,IA,ENVIO_DATOS,EJECUTANDO};

void getMensaje(char* msg);
SentidoGiro getSentidoGiro(char instruccion);
int saveData(char message[], int MAX_LENGTH);
