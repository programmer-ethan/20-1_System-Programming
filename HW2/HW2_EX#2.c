#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc,char* argv[]){
int fd1[2],fd2[2];
int input,output;
int pid1, pid2;
int n;
int status1=0, status2=0;
char buf1[10]="",buf2[10]="";
input=open("input.txt",0);
output=creat("output.txt",0666);
pipe(fd1);
pipe(fd2);
pid1=fork();
if(pid1!=0){//parent면
pid2=fork();
}
if(pid1!=0&&pid2!=0){//parent
  close(fd1[0]);  close(output);
  close(fd2[0]);  close(fd2[1]);
  while((n=read(input,buf1,10))!=0){
    write(fd1[1],buf1,n);//buf1에서 fd1로!
  }
  close(input);   close(fd1[1]);
  waitpid(pid1,&status1,0);
  waitpid(pid2,&status2,0);
}
if(pid1==0){//child1 이면, a->A
  int i;
  close(fd1[1]);    close(fd2[0]);
  close(input);     close(output);
  while((n=read(fd1[0],buf1,10))!=0){
    for(i=0;i<10;i++){
      buf2[i]=toupper(buf1[i]);
    }
    write(fd2[1],buf2,n);
  }
  close(fd2[1]);    close(fd1[0]);
  exit(1);
}
if(pid2==0){
  close(input);   close(fd1[0]);
  close(fd1[1]);  close(fd2[1]);
  while((n=read(fd2[0],buf2,10))!=0){
      write(output,buf2,n);
  }
  close(output);  close(fd2[0]);
  exit(2);
}
return 0;
}
