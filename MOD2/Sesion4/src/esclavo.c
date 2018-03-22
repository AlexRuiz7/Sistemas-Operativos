
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
// Compilar con -lm para solucionar problema de "referencia a sqrt sin definir"
#include<math.h>

//----------------------------------------------------------------------------//

bool esPrimo(unsigned int n){
  if(n==0 || n==1)
    return false;

  for(int i=2; i<=sqrt(n); i++)
    if(n%i == 0)
      return false;

  return true;
}

//----------------------------------------------------------------------------//

int main(int argc, char *argv[]){

//Conversiones de los argumentos de char* a enteros
  int min = strtol(argv[1], NULL, 10);    //Cota inferior del intervalo
  int max = strtol(argv[2], NULL, 10);    //Cota superior del intervalo
  char num[10];                           //Vector para almacenar nº primo
  int fd[2];

  for(int i=min; i<=max; i++)
    if(esPrimo(i)){
      sprintf(num, "%i", i);
      write(fd[1], num, sizeof(int));
    }
  //Se han evaluado todo los números del intervalo. Enviar señal de fin al padre
    sprintf(num, "%i", -1);
    write(fd[1], num, sizeof(char));

  return 0;
}
