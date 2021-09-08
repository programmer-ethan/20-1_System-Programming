#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
  int pid;
  if((pid=fork())==0){
    while(1);
  }
  else{
    kill(pid,SIGKILL);
    printf("send a signal to the child\n");
    wait();
    printf("death of child\n");
  }
}
