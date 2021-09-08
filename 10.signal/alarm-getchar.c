#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define TIMEOUT 3
#define MAXTRIES 5
#define LINESIZE 100
#define CTRL_G '\007'
#define TRUE 1
#define FALSE 0

volatile int timed_out;
char myline[LINESIZE];
void sig_catch(int);

char *quickreply(char *prompt);
  int main(){
    quickreply("login-name:");
  }
  char *quickreply(char *prompt){
    void(*was)(int);
    int ntries,i;
    char *answer;

    was=signal(SIGALRM,sig_catch);
    siginterrupt(SIGALRM,TRUE);

    for(ntries=0;ntries<MAXTRIES;ntries++){
      timed_out=FALSE;
      printf("\n%s>",prompt);
      fflush(stdout);

      alarm(TIMEOUT);

      for(i=0;i<LINESIZE;i++){
        if((myline[i]=getchar())<0)
        break;
        if(myline[i]=='\n'){
          myline[i]=0;
          break;
        }
      }
      alarm(0);
      if(!timed_out){
        printf("%s",myline);
        break;
      }
}//end of retry loop

      answer=myline;
      signal(SIGALRM,was);
      return(ntries==MAXTRIES?((char*)0):answer);
  }

  void sig_catch(int sig_no){
    timed_out=TRUE;
    putchar(CTRL_G);
    fflush(stdout);

    signal(SIGALRM,sig_catch);
  }
