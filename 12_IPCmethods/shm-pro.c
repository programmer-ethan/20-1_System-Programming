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
  else if(signo==SIGINT)
  signal(SIGINT,SIG_DFL);
}


int main(void){
  int shmid;
  size_t shsize=1024;
  const int key= 16000;
  char *shm;
  sem_t *mysem;
  int i;

signal(SIGINT,sig_handler);

sem_unlink("mysem");
if((mysem=sem_open("mysem",O_EXCL| O_CREAT,0777,1))==SEM_FAILED){
  perror("Sem Open Error");
  exit(1);
}
if((shmid==shmget((size_t)key,shsize,IPC_CREAT|0666))<0){
  perror("shmget error");
  exit(1);
}

if((shm=(char*)shmat(shmid,0,0))==(char*)-1){
  perror("shmat");
  exit(1);
}
for(int i=0;i<10;i++){
  shm[i]=0;
}

while(!key_pressed){
  for(i=0;i<10;i++){
    sem_wait(mysem);
    for(int i=0;i<10;i++){
      shm[i]=(shm[i]+1)%10;
    }
    sem_post(mysem);
    sleep(1);
  }
}
while(key_pressed==1){
  for(i=0;i<10;i++){
    sem_wait(mysem);
    for(int i=0;i<10;i++)
    printf("%c",(char)shm[i]);
    sem_post(mysem);
    sleep(1);
    printf("\n\n");
    fflush(stdout);
  }
}
sem_close(mysem);
sem_unlink("mysem");

shmdt(shm);
shmctl(shmid,IPC_RMID,0);

return 0;
}
