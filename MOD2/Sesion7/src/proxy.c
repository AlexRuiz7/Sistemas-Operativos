
//****************************************************************************//
//
//  Fichero PROXY
//
//  Este programa es invocado por el proceso servidor y se encarga de dar
//  soporte a los clientes que se conecten al mismo.
//  Los clientes reciben del servidor el pid del proceso que ejecuta este
//  programa, de manera que puedan comunicarse.
//  Proxy se encarga de crear un FIFO que nombra con su PID para que el cliente
//  pueda reconocerlo, de crear un fichero temporal donde se almacenará todo lo
//  recibido del cliente, a modo de buffer, y de imprimir dicho contenido (por
//  pantalla) una vez el cliente acabe de enviar datos. También maneja un fichero
//  de bloqueo sobre el que se mantendrá un cerrojo para garantizar la
//  exclusión mutua de la pantalla entre los distintos procesos proxy.
//
//  Cada proceso se encarga de eliminar todos los ficheros que ha creado.
//
//****************************************************************************//


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define TAM 1024
#define longnombre 50

//****************************************************************************//
// Recibe la señal TERM, servidor elimina los archivos creados, mata
// proceos hijos zombies y termina su ejecución.

void print_error(char *msg){
  perror(msg);
  exit(EXIT_FAILURE);
}

//****************************************************************************//
// Coloca un cerrojo sobre un archivo abierto, dado su descriptor de archivo.

void bloquear(int fd, int orden){
  struct flock cerrojo;

  cerrojo.l_type    = orden;
  cerrojo.l_whence  = SEEK_SET;
  cerrojo.l_start   = 0;
  cerrojo.l_len     = 0;

  if( fcntl(fd, F_SETLKW, &cerrojo) == -1)
    print_error ("Proxy: Problema en bloqueo/desbloqueo");

}

//****************************************************************************//

int main(int argc, char *argv[]){
  int fd_fifo, fd_bloqueo, bytesLeidos, PID;
  char fifo[longnombre], buffer[TAM];
  FILE *tmp;

  PID = getpid();

  sprintf(fifo, "fifo.%i", PID);
  //printf("Proxy: %s\n", fifo);

  // Apertura del fifo asignado en modo lectura
  if((fd_fifo = open (fifo, O_RDONLY)) == -1)
    print_error ("Proxy: Problema al abrir el archivo fifo");

  // Redirección de entrada al FIFO específico
  dup2(fd_fifo, STDIN_FILENO);

  // Creación del fichero temporal
  if( (tmp = tmpfile())==NULL )
    print_error("Proxy: error al crear el fichero temporal");

  int n, total=0;

  // Leemos lo enviado por el cliente y lo almaceamos en el fichero temporal
  while( (bytesLeidos = read(STDIN_FILENO, buffer, TAM)) >0){
    //printf("Proxy %i: %i bytes leídos de %s\n", PID, bytesLeidos, fifo);
    n = fwrite(buffer, sizeof(char), bytesLeidos, tmp);
    total+=n;
    //printf("Proxy %i: %i bytes escritos en tmp\n", PID, n);
  }

  //printf("Proxy %i: %i bytes recibidos en total\n", PID, total);

  // Cliente ha terminado de enviar datos, y los tenemos en tmp. Los imprimimos.

  // Accedemos al archivo de bloqueo
  if( (fd_bloqueo = open("bloqueo", O_RDWR)) == -1)
    print_error ("Proxy: Problema al abrir el archivo de bloqueo");

  // Bloqueamos el fichero
  bloquear(fd_bloqueo, F_WRLCK);

  // Nos situamos en el principio del archivo.
  fseek(tmp, SEEK_SET, 0);

  // Impresión por pantalla
  printf("\nProxy %i: MENSAJE\n", PID);
/*
  while( !feof(tmp) ){
    bytesLeidos = fread(buffer, sizeof(char), TAM, tmp);
    write(STDOUT_FILENO, buffer, bytesLeidos);
  }
  */
  while( (bytesLeidos = fread(buffer, sizeof(char), TAM, tmp)) != 0)
    write(STDOUT_FILENO, buffer, bytesLeidos);

  // Desbloqueamos el fichero
  bloquear(fd_bloqueo, F_UNLCK);

  printf("\n");
  close(fd_bloqueo);
  close(fd_fifo);
  unlink(fifo);
  exit(0);
}
