#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[]){
  pid_t pid,pid1,pid2;
  int status1,status2, n;
  char buf[10];
  int fd;

  fd=open(argv[1],O_RDONLY);

  pid1=fork();
  if(pid1!=0) pid2=fork();//parent면

  while((n=read(fd,&buf,10))!=0){
    pid=getpid();
    printf("by the pid: %d,",pid);
    printf("10 characters: %s\n",buf);
    strncpy(buf,"\0",10);
    sleep(1);
  }
  close(fd);
  if(pid1==0){
    exit(1);
  }
  else if(pid2==0) exit(2);
  else {
    waitpid(pid1,&status1,0);
    waitpid(pid2,&status2,0);
  }
  return 0;
}
