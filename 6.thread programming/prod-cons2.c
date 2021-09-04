#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *producer(void*);
void *consumer(void*);
#define MAX_BUF 100

int buffer[MAX_BUF];
int count = 0;
int in = -1, out = -1;
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

int main(void){
  int i;
  pthread_t threads[2];
  pthread_create(&threads[0],NULL,producer,NULL);
  pthread_create(&threads[1],NULL,consumer,NULL);
  for (i=0;i<2;i++)
  pthread_join(threads[i],NULL);
  return 0;
}

void *producer (void *v){
  int i;
  for(i=0;i<1000;i++){
    pthread_mutex_lock(&mutex);
    if(count==MAX_BUF){
      printf("is full\n");
      pthread_cond_wait(&buffer_has_space, &mutex);
    }

    in= ++in % MAX_BUF;
    printf("in: %d\n",in);
    buffer[in]=i;
    count++;
    printf("producer count: %d\n",count);
    pthread_cond_signal(&buffer_has_data);
    pthread_mutex_unlock(&mutex);
  }
}

void *consumer(void *v)
{
  int i,data;

  for(i=0;i<1000;i++){
    pthread_mutex_lock(&mutex);
    if(count==0){
      printf("is Empty\n");
      pthread_cond_wait(&buffer_has_data, &mutex);
    }
    out=++out%MAX_BUF;
    printf("out: %d\n",out);
    data=buffer[out];
    count--;
    printf("consumer count: %d\n",count);
    pthread_cond_signal(&buffer_has_space);
    pthread_mutex_unlock(&mutex);
    printf("data = %d\n",data);
  }
}
