
//****************************************************************************//
//
//  Fichero SERVIDOR
//
//  Crea los FIFOS en E/S a por los que se comunican los clientes, y queda
//  activo en modo escucha de manera idefinida hasta que recibe la señal TERM,
//  la cual está programada para que elimine los FIFOS y termine la ejecución.
//  Por cada cliente se lanza un proceso de la clase proxy, que se encargará de
//  dar soporte al cliente asignado, acabando de manera correcta cuando ya no
//  sea necesario.
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

//****************************************************************************//
// Variables globales

#define TAM 1024
#define longnombre 50

// Nombres del FIFO conocido, creado por el servidor.
char nombrefifoe[longnombre], nombrefifos[longnombre];

//****************************************************************************//
// Recibe la señal TERM, servidor elimina los archivos creados, mata
// proceos hijos zombies y termina su ejecución.

static void signal_handler(int signal){
  unlink(nombrefifoe);
  unlink(nombrefifos);
  unlink("bloqueo");

  int estado;
  while (wait(&estado)>0);
  exit(EXIT_SUCCESS);
}

//****************************************************************************//
// Formatea la salida de error estándar con el mensaje dado como parámetro y
// luego finaliza con EXIT_FAILURE

void print_error(char *msg){
  perror(msg);
  exit(EXIT_FAILURE);
}

//****************************************************************************//

int main(int argc, char *argv[]){

  if(argc < 2)
    print_error("Se necesita un nombre para el fifo");

  int fd_fifoe, fd_fifos, bloqueo;    // Descriptores a los FIFO de E/S
  struct sigaction act;               // Para el manejo de señales

  // Establecer nueva acción para la señal TERM y el manejador
  act.sa_handler = signal_handler;
  if(sigaction(SIGTERM, &act, NULL) <0)
    print_error("Servidor: Error al intentar establecer el manejador de señal");

  // Compone los nombres de los FIFOs a partir del parámetro, uno de entrada y
  // otro de salida (desde el punto de vista del servidor).
  sprintf(nombrefifoe,"%se",argv[1]);
  sprintf(nombrefifos,"%ss",argv[1]);

  // Creacción y apertura de archivos FIFO

  if(mkfifo(nombrefifoe, O_RDWR)==-1)
    print_error("Servidor: Problema al crear el archivo fifo de entrada");

  if(mkfifo(nombrefifos, O_RDWR)==-1)
    print_error("Servidor: Problema al crear el archvio fifo de salida");

  if((fd_fifoe = open (nombrefifoe, O_RDWR)) == -1)
    print_error ("Servidor: Problema al abrir el archivo fifo de entrada");

  if((fd_fifos = open (nombrefifos, O_RDWR)) == -1)
    print_error ("Servidor: Problema al abrir el archivo fifo de salida");

  //Creación del fichero de bloqueo
  if( (bloqueo = open("bloqueo", O_RDWR | O_CREAT | S_IRWXU)) == -1 )
    print_error("Servidor: error al crear el fichero de bloqueo.\n");

  // Variables para el manejo de datos
  int bytes_leidos, proxy_PID, c=0;
  char buffer[TAM], *fifo;

  // Entrada de servidor en modo escucha
  while(1){

    if( (bytes_leidos = read(fd_fifoe, buffer, sizeof(int))) > 0){
      c++;
      //printf("Servidor: detectado cliente %i \n", c);

      // Creación de porceso hijo que ejecutará proxy
      if( (proxy_PID = fork()) == -1 )
        print_error("Servidor: problema en fork");

      // Ejecución de proxy
      if(proxy_PID == 0){
        execlp("./proxy", "proxy", NULL);
        exit(EXIT_SUCCESS);
      }
      // Proceso padre
      else{
        // Creación del FIFO con el que se comunicará con el cliente
        sprintf(fifo, "fifo.%i", proxy_PID);
        if(mkfifo(fifo, O_RDWR | S_IRWXU) == -1){
          perror("Proxy: Problema al crear el archivo fifo");
          exit(EXIT_FAILURE);
        }
        // Se envia a cliente el pid del proxy
        write(fd_fifos, &proxy_PID, sizeof(int));
      } // else
    } // if
  } // while
} // main
