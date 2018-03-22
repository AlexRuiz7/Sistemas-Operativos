#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

  if(argc < 4){
    printf("\nModo de ejecución: ./ejer1 <orden_linux> '<' o '>' <fichero>");
    exit(EXIT_FAILURE);
  }

  if( !strcmp(argv[2], "<") && !strcmp(argv[2], ">") ){
    printf("\nFallo en 2 argumento: .deber ser < ó >");
    exit(EXIT_FAILURE);
  }

  int fd;

  if((fd=open(argv[3], O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR))<0){
    perror("fallo en open");
    exit(EXIT_FAILURE);
  }

  if( strcmp(argv[2], "<")==0 ){        // Redirección de entrada estándar
    printf("Entrada estándar\n");
    close(0);                           // Cerrar entrada estándar
    if(fcntl(fd, F_DUPFD, 0)==-1)       // Duplicar descriptor de archivo
      perror("Fallo en fcntl. Redirección de entrada");
    execlp(argv[1], argv[1], NULL);
  }
  if( strcmp(argv[2], ">")==0 ){        // Redirección de salida estándar
    printf("Salida estándar\n");
    close(1);                           // Cerrar salida estándar
    if(fcntl(fd, F_DUPFD, 1)==-1)       // Duplicar descriptor de archivo
      perror("Fallo en fcntl. Redirección de salida");
    execlp(argv[1], argv[1], NULL);
  }

  close(fd);

  return 0;
}
