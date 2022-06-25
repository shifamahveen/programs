#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<string.h>
main(int argc,char *argv[]){
struct sockaddr_in s,c;
int i,n,pid,sockid,rval,clen,newsockid;
char m1[255],m2[255];
time_t t;
system("clear");
if(argc<3)
{
printf("\n usage error%s IPaddr,port\n",argv[0]);
exit(1);
}
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid== -1){
perror("SOCR_CRE_ERR");
exit(1);
}
printf("socket created\n");
s.sin_family=AF_INET;
s.sin_addr.s_addr = inet_addr(argv[1]);
s.sin_port = htons(atoi(argv[2]));
rval = bind(sockid,(struct sockaddr *)&s,sizeof(s));
if(rval==-1){
perror("err_bind");
exit(1);
}
printf("bind created");
rval=listen(sockid,5);
clen=sizeof(c);
for(i=1;i<=n;i++){
newsockid=accept(sockid,(struct sockaddr*)&c,&clen);
printf("\nAccepting...");
pid=fork();
if(pid==-1){
perror("\nError in creating child process");
exit(1);
}
if(pid==0){
rval=recv(newsockid,m1,sizeof(m1),0);
if(rval == -1)
{
perror("ERR_RCV");
exit(1);
}
printf("message received from client is %s\n",m1);
t=time(0);
strcpy(m2,ctime(&t));
rval=send(newsockid,m2,sizeof(m2),0);
if(rval == -1)
{
perror("ERR_SND");
exit(1);
}
printf("message sent to server is %s\n",m2);
close(newsockid);
exit(0);
}
else
close(newsockid);
}
close(sockid);
}




