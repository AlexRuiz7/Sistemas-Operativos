#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

  if(argc<3){
    printf("Modo de ejecución: ./ejer5 <archivo_fuente> <arhcivo_destino>\n");
    exit(-1);
  }

  char *copia;
  int fd;
  off_t size;

  if((fd=open(argv[1], O_RDONLY))==-1){
    perror("Error en open fuente");
    exit(-1);
  }

  if((fd=open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU))==-1){
    perror("Error en open destino");
    exit(-1);
  }

  size = stat(fd).st_size;
  copia = (char *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (memoria == MAP_FAILED) {
      perror("Fallo la proyeccion");
      exit(2);
  }



  return 0;
}
