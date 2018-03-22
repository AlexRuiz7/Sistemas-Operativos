
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

#define S_ISREG2(mode) ((mode & S_IFMT) == S_IFREG)

int main(int argc, char *argv[]){
  int i;
  struct stat atributos;
  char tipoArchivo[30];

  if(argc<2) {
  	printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
  	exit(-1);
  }
  for(i=1;i<argc;i++) {
  	printf("%s: ", argv[i]);
  	if(lstat(argv[i],&atributos) < 0) {
  		printf("\nError al intentar acceder a los atributos de %s",argv[i]);
  		perror("\nError en lstat");
  	}
  	else {
  		if(S_ISREG2(atributos.st_mode))
        strcpy(tipoArchivo,"Regular");
      else
        strcpy(tipoArchivo,"Fallo");
      printf("%s\n",tipoArchivo);
  	}
  }

  return 0;
}
