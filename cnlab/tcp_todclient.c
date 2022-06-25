#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
main(int argc, char *argv[])
{
	unsigned long tempval,timeval;
	struct sockaddr_in s;
	int sockid, rval, slen;
	char m1[20],m2[255];
	system("clear");
	if(argc<3)
	{
		printf("\nUsage error:%sIP addr,Port\n",argv[0]);
		exit(1);
	}
	sockid=socket(AF_INET,SOCK_STREAM,0);
	if(sockid==-1)
	{
		perror("SOCK_CRE_ERR");
		exit(1);
	}
	s.sin_family=AF_INET;
	s.sin_addr.s_addr=inet_addr(argv[1]);
	s.sin_port=htons(atoi(argv[2]));
	rval=connect(sockid,(struct sockaddr *)&s,sizeof(s));
        printf("Enter the message\n");
	scanf("%s",m1);
	slen=sizeof(s);
	rval=send(sockid,m1,sizeof(m1),0);
	if(rval==-1)
	{
		perror("ERR_in_SND");
		exit(1);
	}
	printf("Message sent successfully\n");
	rval=recv(sockid,&tempval,sizeof(tempval),0);
	if(rval==-1)
	{
		perror("ERR_in_RCV");
		exit(1);
	}
	timeval=htonl(tempval);
	printf("Message received successfully: %u\n",timeval);
	close(sockid);
}


