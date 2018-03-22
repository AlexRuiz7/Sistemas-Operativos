#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

  if(argc < 3){
    printf("\nModo de ejecución: ./ejer2 <orden_linux> '|' <orden_linux>");
    exit(EXIT_FAILURE);
  }

  if( strcmp(argv[2], "|")!=0 ){
    printf("\nFallo en 2 argumento: .deber ser |");
    exit(EXIT_FAILURE);
  }

  int fd[2];
  pid_t PID;

  pipe(fd);

  if ( (PID= fork())<0) {
    perror("\nError en fork");
    exit(EXIT_FAILURE);
  }

  if (PID == 0) { // porceso hijo, ls
    close(fd[0]);     // Cerrar entrada estándar en el proceso hijo

    if( fcntl(fd[1], F_DUPFD, 0)==-1 )  // Duplicar salida estándar
      perror("Fallo en fcntl 1");
    execlp(argv[1], argv[1], NULL);
  }
  else { // sort. Proceso padre porque PID != 0.
    close(fd[1]);     // Cerrar salida estándar en el proceso padre
    if( fcntl(fd[0], F_DUPFD, 1)==-1 )  // Duplicar entrada estándar
      perror("Fallo en fcntl 2");
    execlp(argv[3], argv[3], NULL);
  }

  return 0;
}
