#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
static void sig_catcher(int);
int alarmed=0;

int main(){
  int pid;
  signal(SIGALRM,sig_catcher);
  alarm(3);
  do something;
  while(alarmed==0);
  printf("after alarm in main\n");
}
void sig_catcher(int signo){
  alarmed=1;
  alarm(0);
}
