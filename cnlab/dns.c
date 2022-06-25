#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

main(int argc,char *argv[]){
	int sock_id,rval,slen;
	struct sockaddr_in s,c;
	char sym[253],ip[255];
	system("clear");
	if(argc<3){
		printf("\nUsage : %s IP address,Port No",argv[0]);
		exit(1);
	}
	sock_id=socket(AF_INET,SOCK_DGRAM,0);
	if(sock_id==-1){
		perror("SOCK_CRE_ERR");
		exit(1);
	}
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr(argv[1]);
	s.sin_port = htons(atoi(argv[2]));
	printf("\nEnter the symbolic name of the resource\n");
	scanf("%s",sym);
	slen = sizeof(s);
	rval = sendto(sock_id,sym,sizeof(sym),0,(struct sockaddr *)&s, slen);
	if(rval==-1){
		perror("ERR\n");
		exit(1);
	}
	printf("Waiting for response from resource\n");
	rval = recvfrom(sock_id,ip,sizeof(ip),0,(struct sockaddr *)&s,&slen);
	if(rval==-1){
		perror("ERR");
		exit(1);
	}
	printf("\nThe IP address at %s is %s",sym,ip);
	close(sock_id);
}
