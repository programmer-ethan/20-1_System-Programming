#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>

void *threadFunc(void *arg){
  int count =0;
  printf("new thread started ....\n");
  int retval;
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
  while(1){
    printf("count = %d \n", count++);
    sleep(1);
    pthread_testcancel();

    if(count==10)break;
  }
  pthread_exit((void*)count);
}
int main(int argc,char *argv[])
{
  pthread_t tid;
  int retval;
  void *res;

  pthread_create(&tid,NULL,threadFunc,NULL);
  sleep(5);
  pthread_cancel(tid);
  retval=pthread_join(tid,&res);
  if(retval!=0){
    perror("pthread_join : ");
    exit(EXIT_FAILURE);
  }
  if(res==PTHREAD_CANCELED)//????
  printf("thread cancelled\n");
  else
  printf("thread is normal exit retval = %d \n",(int)res);

  exit(EXIT_SUCCESS);
}
