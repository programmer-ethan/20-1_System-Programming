#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 1024
#define PORT 30000
#define BACKLOG 5

int main(int argc,char *argv[]){
int sd, nsd, pid, bytes, cliaddrsize;
struct sockaddr_in cliaddr, servaddr;
char data[MAX];


if((sd=socket(AF_INET,SOCK_STREAM,0))<0){
  fprintf(stderr,"can't open socket.\n");
  exit(1);
}


bzero((char*)&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addrs.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);

if(bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
  fprintf(stderr,"can't bind to socket.\n");
  exit(1);
}
listen(sd,BACKLOG);

while(1){
  cliaddrsize=sizeof(cliaddr);
  if(nsd=accept(sd,(struct sockaddr*)&cliaddr,&cliaddrsize))<0){
    fprintf(stderr,"can't accept connection.\n");
    exit(1);
  }
  if((pid=fork())<0){
    fprintf(stderr,"can't fork process.\n"); exit(1);
  }
  if(pid==0){
    close(sd);
    while(1){
      bytes=recv(nsd,data,MAX,0);
      if(bytes==0){
        break;
      }
      else if(bytes<0){
        fprintf(stderr,"can't receive data.\n"); exit(1);
      }
      if(send(nsd,data,bytes,0)!=bytes){
        fprintf(stderr,"can't send data.\n"); exit(1);
      }
    }
    return 0;
  }
  else
  close(nsd);
}
}
