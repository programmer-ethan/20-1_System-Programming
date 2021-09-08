#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
  printf("Self Process signal : \n");
  raise(SIGUSR1);
}
