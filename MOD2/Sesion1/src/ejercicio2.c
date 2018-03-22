

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){

  // Comprobamos que recibimos un argumneto

  if(argc != 2){
    printf("\nSintaxis de ejecución: ejercicio2 <nombre_archivo>\n");
    exit(-1);
  }

  // Datos

  int fd_r, fd_w;
  char buf[80];
  int i=1;        //Nº de bytes leídos/escritos
  int bloques=1;  // Nº de bloques
  char linea[40]; // Línea de texto para indicar el nº de bloque

  // Abrimos el fichero a leer(dado como parémetro)

  if((fd_r = open(argv[1], O_RDONLY, S_IRUSR))<0){
    printf("\nError %d en open", errno);
  	perror("\nError en open de archivo");
  	exit(EXIT_FAILURE);
  }

  // Abrimos (o creamos si es necesario) el fichero de salida "salida.txt"

  if((fd_w = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR))<0){
    printf("\nError %d en open", errno);
  	perror("\nError en open de salida.txt");
  	exit(EXIT_FAILURE);
  }

  // Reserva de espacio al comienzo del fichero de salida para indicar el nº
  // de bloques total.

  lseek(fd_w, 40, SEEK_SET);

  // El nº de bytes leídos se almacena en i, que es el nº de bytes escritos en
  // salida.txt en el write. Se leen 80 bytes en cada iteración salvo en la última,
  // en la que i<=80.

  while((i=read(fd_r, buf, 80)) != 0){

    // Escritura en fichero del número de bloque actual.
    sprintf(linea, "\n\n#### Bloque %i ####\n\n", bloques);
    write(fd_w, linea, strlen(linea));
    bloques++;

    // Escritura en salida.txt de los bytes leídos almacenados en buf.
    if(write(fd_w, buf, i) != i){
      perror("\nError en write");
  	  exit(EXIT_FAILURE);
    }

  }

  // Escritura del número total de bloques al comienzo del fichero salida.txt
  bloques--;
  sprintf(linea, "\n$$ Número total de bloques: %i $$", bloques);
  lseek(fd_w, 0, SEEK_SET);
  write(fd_w, linea, strlen(linea));

  // Cierre de ficheros y salida con éxito.
  close(fd_r);
  close(fd_w);
  return EXIT_SUCCESS;
}
