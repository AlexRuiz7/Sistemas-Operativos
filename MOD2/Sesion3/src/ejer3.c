#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

// Probar los 2 trozos de código independientementes, comentandolos.

int main(){

  pid_t childpid, parentpid;
  int nprocs = 20;

  /*
  Jerarquía de procesos tipo 1
  */
  
  printf("JERARQUIA TIPO 1\n\n");
  for (int i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
        fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
        exit(-1);
    }

    if (childpid)
      break;

    parentpid = getppid();
    printf("\nChild PID: %d\tParent PID: %d\n", childpid, parentpid);
  }

  /*
  Jerarquía de procesos tipo 2
  */
  /*
  printf("JERARQUIA TIPO 2\n\n");
  for (int i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }

    if (!childpid)
      break;

    parentpid = getppid();
    printf("\nChild PID: %d\tParent PID: %d\n", childpid, parentpid);
  }
*/
  exit(0);
}
