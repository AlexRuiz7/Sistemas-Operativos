#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

  if(argc <2){
    printf("modo de ejecución: ./ejer3 <archivo>\n");
    exit(-1);
  }

  struct flock cerrojo_r, cerrojo_w;
  int fd;

  if((fd=open(argv[1], O_RDWR))==-1){
    perror("Fallo en open");
    exit(-1);
  }

  // Bloqueo de lectura al archivo completo
  cerrojo_r.l_type=F_RDLCK;
  cerrojo_r.l_whence=SEEK_SET;
  cerrojo_r.l_start=0;
  cerrojo_r.l_len=0;

  // Bloqueo de escritura al archivo completo
  cerrojo_w.l_type=F_WRLCK;
  cerrojo_w.l_whence=SEEK_SET;
  cerrojo_w.l_start=0;
  cerrojo_w.l_len=0;

  if(fcntl(fd, F_SETLKW, &cerrojo_r)==-1)
    perror("Fallo en cerrojo de lectura\n");
  if(fcntl(fd, F_SETLKW, &cerrojo_w)==-1)
    perror("Fallo en cerrojo de escritura\n");

  printf("Cerrojos activados.\nDesbloqueando...\n");

  if(fcntl(fd, F_UNLCK, &cerrojo_r)==-1)
    perror("Fallo en desbloqueo de lectura\n");
  if(fcntl(fd, F_UNLCK, &cerrojo_w)==-1)
    perror("Fallo en desbloqueo de escritura\n");

  printf("Cerrojos desactivados.\n");

  return 0;
}
