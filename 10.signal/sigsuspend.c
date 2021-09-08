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

void sig_catch(int sig_no){
  printf("sig_catch, %d\n",sig_no);
}
int main(){
  sigset_t mysigset, oldsigset;
  sigemptyset(&mysigset);
  sigaddset(&mysigset,SIGUSR1);
  signal(SIGUSR1,sig_catch);
  sigprocmask(SIGUSR1,sig_catch);
if((pid=fork())==0){
  sigsuspend(&oldsigset);
  printf("Child wake up\n");
  exit(0);
}
else{
  sleep(1);
  kill(pid,SIGUSR1);
  wait();
}
}
