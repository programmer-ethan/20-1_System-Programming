#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>


int main(void){//send

time_t curtime,mktime;
struct tm *tmbuf;

if(time(&curtime)<0){
perror("time error");
exit(1);
}
printf("curtime time from Epoch(UTC) : %d secs\n", (int)curtime);
printf("Result of time : %s\n",ctime(&curtime));

tmbuf=(struct tm*) localtime(&curtime);
printf("Result of asctime : %s\n",asctime(&tmbuf));
}
