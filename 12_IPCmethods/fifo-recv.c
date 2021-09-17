#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define SIZE 128
#define FIFO "fifo"

int main(int argc,char *argv[]){
  int fd;
  char buffer[SIZE];

  if(mkfifo(FIFO,0666)==-1){
    perror("mkfifo failed");
    exit(1);
  }
  if((fd=open(FIFO,O_RDWR))==-1){
    perror("open failed");
    exit(1);
  }

while(1){
  if(read(fd,buffer,SIZE)==-1){
    perror("read failed");
    exit(1);
  }
  if(!strcmp(buffer,"quit"))
  exit(0);
  printf("receive message: %s\n",buffer);
}
}
