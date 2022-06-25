#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

main(int argc,char *argv[]){
	struct sockaddr_in s,c;
	int sockid,rval,clen;
	char m1[20];
	system("clear");
	if(argc<3){
		printf("\nUsage error: %s IPADDR,port\n",argv[0]);
		exit(1);
	}
	sockid=socket(AF_INET,SOCK_DGRAM,0);
	if(sockid==-1){
		perror("\nSOCK_CRE_ERR");
		exit(1);
	}
	printf("\nsocket created");
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr(argv[1]);
	s.sin_port = htons(atoi(argv[2]));
	rval = bind(sockid,(struct sockaddr *)&s,sizeof(s));
	if(rval==-1){
		perror("\nERR_IN_BIND");
		exit(1);
	}
	printf("\nbinded successfully");
	clen=sizeof(c);
	rval=recvfrom(sockid,m1,sizeof(m1),0,(struct sockaddr *)&s,&clen);
	if(rval==-1){
		perror("\nERR_IN_RECV");
		exit(1);
	}
	printf("\nMessage recieved by server successfully");
	rval=sendto(sockid,m1,sizeof(m1),0,(struct sockaddr *)&s,&clen);
	if(rval==-1){
		perror("\nError in sending");
		exit(1);
	}
	printf("\nmessage sent to client is: %s",m1);
	close(sockid);
}
