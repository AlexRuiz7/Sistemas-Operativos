/*
ejercicio5.c
Programa en el que se sigue el esquema maestro-esclavo. El programa
recibe un intervalo de números como argumento y crea dos procesos hijos que
calculan los números primos en dicho intervalo. Cada proceso hijo calcula los
números en una mitad del intervalo.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main(int argc, char *argv[]){

  pid_t PID1, PID2;
  char * min, medio[10], *max;        // Subintervalos
  int fd1[2], fd2[2], numBytes, temp;
  char numero[10];

//Comprobar argumentos e informar de la forma correcta  de ejecutar el programa
  if( (argc != 3) ){
    printf("\nEjecución: ejercicio5 min_intervalo max_intervalo");
    exit(-1);
  }

//Conversiones y manejo del intervalo dado como parámetro
  min = argv[1];                      //Límite inferior del intervalo
  max = argv[2];                      //Límite superior del intervalo
  //Punto medio del intervalo = (min + max) / 2
  temp = (strtol(argv[1], NULL, 10)+strtol(argv[2], NULL, 10))/2;
  sprintf(medio,"%i", temp);          //Reconversion a char *

//Comprobar que el intervalo es válido. Creciente
  if(min > max){
    printf("\nNecesita dar dos números enteros que formen un intervalo válido(a>0 y a<b).");
    exit(-1);
  }

// Creación del cauce para hijo 1
  pipe(fd1);

//Creación del hijo 1
  if( (PID1= fork())<0){
    perror("Error en fork 1");
    exit(-1);
  }

// Asignar trabajo a hijo 1
  if(PID1 == 0){
    //Cerrar descriptor de lectura en el proceso hijo
    close(fd1[0]);
    printf("\n\n[hijo 1] %d \tCalculando numeros primos de %s a %s\n", getpid(), min, medio);
    dup2(fd1[1], STDIN_FILENO);
    execlp("./esclavo", "esclavo", min, medio, NULL);
    exit(0);
  }
//Proceso padre.
  else{
    //Lectura desde el cauce con el hijo 1
    printf("\n[padre]\tEsperando a hijo 1");
    while( (numBytes =read(fd1[0], &numero, sizeof(int)) ) == sizeof(int) )
      printf("\nHe recibido el nº primo %s", numero);
    if(numBytes<0)
      perror("Error en read");

//----------------------------------------------------------------------------//

    // Creación del cauce para hijo 2
    pipe(fd2);

    //Creación del hijo 2
    if( (PID2= fork())<0){
      perror("Error en fork 2");
      exit(-1);
    }
    //Asignar trabajo a hijo 2
    if(PID2 == 0){
      //Cerrar descriptor de lectura en el proceso hijo
      close(fd2[0]);
      printf("\n\n[hijo 2] %d \tCalculando numeros primos de %s a %s\n", getpid(), medio, max);
      dup2(fd2[1], STDIN_FILENO);
      execlp("./esclavo", "esclavo", medio, max, NULL);
      exit(0);
    }
    //Lectura desde el cauce con el hijo 2
    else{
      printf("\n[padre]\tEsperando a hijo 2");
      while( (numBytes =read(fd2[0], &numero, sizeof(int)) ) == sizeof(int) )
        printf("\nHe recibido el nº primo %s", numero);
      if(numBytes<0)
        perror("Error en read");
    }
  }

  return 0;
}
