#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>

int key_pressed =0;

static void sig_handler(int signo){
  key_pressed++;
  printf("continue to thr next stage.... \n");
  if(key_pressed==1&&signo==SIGINT)
  signal(SIGINT,sig_handler);
  else if (signo==SIGINT)
  signal(SIGINT,SIG_DFL);
}


int main(void){
  int shmid;
  size_t shsize=1024;
  const int key= 16000;
  char *shm;
  char c;
  sem_t *mysem;
  int i;

signal(SIGINT,sig_handler);

if((mysem=sem_open("mysem",0,0777,0))==SEM_FAILED){
  perror("Sem Open Error");
  exit(1);
}
if((shmid==shmget((size_t)key,shsize,IPC_CREAT|0666))<0){
  perror("shmget");
  exit(1);
}

if((shm=(char*)shmat(shmid,NULL,0))==(char*)-1){
  perror("shmat");
  exit(1);
}
while(!key_pressed){
  for(i=0;i<10;i++){
    sem_wait(mysem);
    for(int i=0;i<10;i++)
      printf("%d",(shm[i]));
    putchar('\n');
    sem_post(mysem);
    sleep(1);
  }
}
while(key_pressed==1){
  c='A';
  for(i=0;i<10;i++){
    sem_wait(mysem);
    for(int i=0;i<10;i++)
      shm[i]=c;
    sem_post(mysem);
    sleep(1);
    if(++c>'Z')c='A';
  }
}
sem_close(mysem);
shmdt(shm);

return 0;
}
