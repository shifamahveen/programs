#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
main(int argc, char *argv[])
{
	struct sockaddr_in s,c;
	int sockid, rval, clen, newsid;
	char m1[255];
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
	rval=bind(sockid,(struct sockaddr *)&s,sizeof(s));
	if(rval==-1)
	{
		perror("ERR_IN_BINDING");
		exit(1);
	}
	printf("Server binded successfully\n");
	rval=listen(sockid,5);
	if(rval==-1)
	{
		perror("ERR_IN_LISTENING");
		exit(1);
	}
	printf("Successfully listening\n");
	clen=sizeof(c);
	newsid=accept(sockid,(struct sockaddr *)&c,&clen);
	if(newsid==-1)
	{
		perror("ERR_in_NewSocketCreation");
		exit(1);
	}
	printf("New socket created successfully\n");
	rval=recv(newsid,m1,sizeof(m1),0);
	if(rval==-1)
	{
		perror("ERR_in_RCV");
		exit(1);
	}
	printf("Message received successfully: %s\n",m1);
	rval=send(newsid,m1,sizeof(m1),0);
	if(rval==-1)
	{
		perror("ERR_in_SND");
		exit(1);
	}
	printf("Message sent successfully:\n");
	close(sockid);
	close(newsid);
}

