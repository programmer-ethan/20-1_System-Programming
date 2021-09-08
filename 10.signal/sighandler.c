#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sigcatcher(int);
void(*was)(int);

int main(void){
  if(was=signal(SIGINT,sigcatcher)==SIG_ERR){
    perror("SIGINT");
    exit(1);
  }
  while(1) pause();
}

static void sigcatcher(int signo){
  switch(signo){
    case SIGINT :
    printf("PID %d caught signal SIGINT.\n",getpid());
    signal(SIGINT,was);
    break;
    default:
    fprintf(stderr,"something wrong\n");
    exit(1);
  }
}
