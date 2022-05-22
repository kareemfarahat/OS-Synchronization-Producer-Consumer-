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
/* convert upper case to lower case or vise versa */
void conv(char* msg, int size)
{
    int i;
    for (i = 0; i < size; ++i)
        if (islower(msg[i]))
            msg[i] = toupper(msg[i]);
        else if (isupper(msg[i])) msg[i] = tolower(msg[i]);

};
int main(){
 struct msgbuff message ;
 int upmsgqid = msgget( 1 , IPC_CREAT | 0666 );
 if (upmsgqid < 0)
 {
     perror( "faild to create up queue\n");
 }
 
 int downmsgqid = msgget(2 , IPC_CREAT | 0666 );
 if (downmsgqid < 0)
 {
     perror( "faild to create down queue\n");
 }
 printf("waiting");
 msgrcv( upmsgqid , &message.mtext , sizeof(message)- sizeof(long), 0, !IPC_NOWAIT);

 conv(message.mtext, sizeof(message.mtext));
 int sendval = msgsnd (downmsgqid , &message , sizeof(message)- sizeof(long), message.mtype);
if (sendval < 0)
{
perror( "faild to send \n");
}



return 0;
}