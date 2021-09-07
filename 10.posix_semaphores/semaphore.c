#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
int cnt=0;
static sem_t hsem;

void *Thread1(void *arg);
void *Thread2(void *arg);

int main(int argc,char *argv[]){
  pthread_t thread1;
  pthread_t thread2;

  if(sem_init(&hsem,0,1)<0){
    fprintf(stderr,"Semaphore Initialization Error\n");
    return 1;
  }
  pthread_create(&thread1,NULL,Thread1,NULL);
  pthread_create(&thread2,NULL,Thread2,NULL);
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
  printf("%d\n",cnt);
  sem_destroy(&hsem);

  return 0;
}
void *Thread1(void *arg){
  int i, tmp;

  for(i=0;i<1000;i++){
    sem_wait(&hsem);
    tmp=cnt;
    usleep(1000);
    cnt=tmp+1;
    sem_post(&hsem);
  }
  printf("Thread1 End\n");

  return NULL;
}

void *Thread2(void *arg){
  int i, tmp;

  for(i=0;i<1000;i++){
    sem_wait(&hsem);
    tmp=cnt;
    usleep(1000);
    cnt=tmp+1;
    sem_post(&hsem);
  }
  printf("Thread2 End\n");

  return NULL;
}
