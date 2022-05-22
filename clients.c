  #include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
struct msgbuff
{
    long mtype;
    char mtext[256];
};

int main(){
 struct msgbuff message ;
 message.mtype = getpid();
 int upmsgqid = msgget(1 , 0 );
 if (upmsgqid < 0)
 {
     perror( "faild to connect  up queue\n");
 }
 int downmsgqid = msgget(2 , 0  );
 if (downmsgqid < 0)
 {
     perror("faild to connect down queue\n");
 }
 printf ("please Enter YOUR message ^__^ \n");
 scanf("%s",message.mtext );
 int sendval = msgsnd (upmsgqid , &message , sizeof(message)- sizeof(long), !IPC_NOWAIT);
if (sendval < 0)
{
perror( "faild to send \n");
}
printf("waiting the results\n");
 int receveval = msgrcv ( downmsgqid , &message.mtext , sizeof(message)- sizeof(long), message.mtype , !IPC_NOWAIT);
if (receveval < 0)
{
perror( "faild to get tet \n");
}
printf("your result is\n %s \n", message.mtext);

return 0;
}
