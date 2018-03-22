#include <stdio.h>
#include <signal.h>

/*  SEÑALES
  SIGHUP  - 0
  SIGINT  - 1
  SIGQUIT - 2
  SIGILL  - 3
  SIGABRT - 4
  SIGFPE  - 5
  SIGKILL - 6   // No manejable
  SIGSEGV - 7
  SIGPIPE - 8
  SIGALRM - 9
  SIGTERM - 10
  SIGUSR1 - 11
  SIGUSR2 - 12
  SIGCHLD - 13
  SIGCONT - 14
  SIGSTOP - 15  // No manejable
  SIGTSTP - 16
  SIGTTIN - 17
  SIGTTOU - 18

    FIN SEÑALES */

static int s_hup, s_int, s_quit, s_ill, s_abrt, s_fpe, s_segv, s_pipe, s_alrm,
           s_term, s_usr1, s_usr2, s_chld, s_cont, s_tstp, s_ttin, s_ttou;

static void contador(int signum){
  switch(signum){
    case 0:
      s_hup++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_hup);
      break;
    case 1:
      s_int++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_int);
      break;
    case 2:
      s_quit++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_quit);
      break;
    case 3:
      s_ill++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_ill);
      break;
    case 4:
      s_abrt++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_abrt);
      break;
    case 5:
      s_fpe++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_fpe);
      break;
    case 7:
      s_segv++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_segv);
      break;
    case 8:
      s_pipe++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_pipe);
      break;
    case 9:
      s_alrm++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_alrm);
      break;
    case 10:
      s_term++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_term);
      break;
    case 11:
      s_usr1++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_usr1);
      break;
    case 12:
      s_usr2++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_usr2);
      break;
    case 13:
      s_chld++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_chld);
      break;
    case 14:
      s_cont++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_cont);
      break;
    case 16:
      s_tstp++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_tstp);
      break;
    case 17:
      s_ttin++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_ttin);
      break;
    case 18:
      s_ttou++;
      printf("\nLa señal %i se ha recibido %i veces\n", signum, s_ttou);
      break;
    default:
      printf("\nNo se reconoce esa señal\n");
      break;
  }

}

int main(){
  struct sigaction sa;
  sigset_t mask;

  sa.sa_handler = contador;
  sigfillset(&mask);

  sigaction(SIGHUP,&sa, NULL);
  sigaction(SIGINT,&sa, NULL);
  sigaction(SIGQUIT,&sa, NULL);
  sigaction(SIGILL,&sa, NULL);
  sigaction(SIGABRT,&sa, NULL);
  sigaction(SIGFPE,&sa, NULL);
  sigaction(SIGSEGV,&sa, NULL);
  sigaction(SIGPIPE,&sa, NULL);
  sigaction(SIGALRM,&sa, NULL);
  sigaction(SIGTERM,&sa, NULL);
  sigaction(SIGUSR1,&sa, NULL);
  sigaction(SIGUSR2,&sa, NULL);
  sigaction(SIGCHLD,&sa, NULL);
  sigaction(SIGCONT,&sa, NULL);
  sigaction(SIGTSTP,&sa, NULL);
  sigaction(SIGTTIN,&sa, NULL);
  sigaction(SIGTTOU,&sa, NULL);

  while(1);

}
