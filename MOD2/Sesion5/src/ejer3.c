#include <stdio.h>
#include <signal.h>

int main(){
  sigset_t mask;

  sigfillset(&mask);

  sigdelset(&mask, SIGUSR1);

  sigsuspend(&mask);
}
