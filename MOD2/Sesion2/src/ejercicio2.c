
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>


int main(int argc, char const *argv[]){

  /* Comprobamos los argumentos */
  if(argc != 3){
    printf("\nSintaxis de ejecucion: ejercicio2 [<Directorio>] [nuevos_permisos_en_octal] \n\n");
  	exit(-1);
  }

  /* Variables */
  DIR *d;
  struct dirent *ds;
  char *ptr, *fichero;
  long permisos;
  permisos = strtol(argv[2], &ptr, 8);
  //printf("permisos: %o", permisos);

  // Abrimos el directorio //
  d = opendir(argv[1]);
  if(d == NULL){
    printf("Error: No se puede abrir el directorio\n");
    exit(2);
  }

  // Leemos las entradas del directorio //
  while((ds = readdir(d)) != NULL){
    fichero = ds->d_name;
    printf("\nFichero: %s", fichero);
    if(chmod(fichero, permisos)<0)
      perror("\nError al cambiar permisos");
    else
      printf("\tPermisos: %o", permisos);
  }

  // Cerramos el directorio //
  closedir(d);
}
