#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

  pid_t pid;
  int estado, n=5;

  for(int i=0; i<n; i++){
    if( (pid=fork()) <0){
      printf("Error en fork");
      exit(-1);
    }
    if(pid==0)
      break;
    printf("\nSoy el hijo %d\tMi padre es %d", pid, getppid());
    fflush(stdout);
    pid = wait(&estado);
    printf("\nAcaba de finalizar mi hijo %d", pid);
    fflush(stdout);
    printf("\nSolo me quedan %i hijos vivos", n-i-1);
    fflush(stdout);
  }
  exit(0);
}
