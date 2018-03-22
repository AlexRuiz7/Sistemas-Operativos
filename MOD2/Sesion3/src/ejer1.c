#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  if(argc < 2)
    printf("\nUso: ./ejer1 <numero_entero>");

  pid_t pid;
  int numero = strtol(argv[1], (char **)NULL, 10);

  if( ( pid=fork() )<0){
    	perror("\nError en el fork");
    	exit(-1);
  }

  if(pid==0){
    printf("\n\nProceso hijo.\n");
    if(numero%2==0) printf("\nEs un nº par");
    else            printf("\nEs un nº impar");
  }
  else{
    printf("\n\nProceso padre.\n");
    if(numero%4==0) printf("\nEs divisible por 4");
    else            printf("\nNo es divisible por 4");
  }

  exit(0);
}
