#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void alarm_handler(int signo){
  printf("Timer hit\n");
}

int main(){
  struct itimerval delay;
  int ret;
  signal(SIGALRM,alarm_handler);
  delay.it_value.tv_sec=5;
  delay.it_value.tv_usec=0;
  delay.it_interval.tv_sec=1;
  delay.it_interval.tv_usec=0;
  ret=setitimer(ITIMER_REAL,&delay,NULL);
  if(ret){
    perror("setitimer");
    exit(0);
  }
  while(1){
    pause();
  }
}
