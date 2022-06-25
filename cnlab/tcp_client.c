#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

main(int argc,char *argv[]){
	int sockid,rval,slen;
	struct sockaddr_in s,c;
	char m1[253],m2[255];
	system("clear");
	if(argc<3){
		printf("\nUsage error: %s IPADDR, port\n",argv[0]);
		exit(1);
	}
	sockid = socket(AF_INET,SOCK_STREAM,0);
	if(sockid==-1){
		perror("\nSOCK_CRE_ERR");
		exit(1);
	}
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr(argv[1]);
	s.sin_port = htons(atoi(argv[2]));
	
	slen = sizeof(s);
	rval = connect(sockid,(struct sockaddr *)&s,slen);
	if(rval==-1){
		perror("\nERR_IN_CONN");
		exit(1);
	}
	printf("enter the message\n");
	scanf("%s",m1);
	printf("\nMessage sent successfully");
	rval = send(sockid,m1,sizeof(m1),0);
	if(rval==-1){
		perror("Error in sending");
		exit(1);
	}
	printf("\nmessage sent succesfully");
	rval=recv(sockid,m2,sizeof(m2),0);
	if(rval==-1)
	{
		printf("error in recv\n");
		exit(1);
	}
	printf("\nMessage recieved is: %s",m2);
	close(sockid);
}
