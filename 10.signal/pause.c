#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>


void sig_catch(int signo){
    printf("PID %d caught signal.\n",getpid());
    exit(1);
}

int main(){
  int pid;
  int status;
  signal(SIGUSR1,sig_catch);
  if((pid=fork())==0){
    pause();
    printf("Child wake up\n");
    exit(0);
  }else{
    sleep(1);
    kill(pid,SIGUSR1);
    wait(&status);
  }
}
