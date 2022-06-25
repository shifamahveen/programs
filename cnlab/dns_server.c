#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
main(int argc,char *argv[]){
	struct sockaddr_in s,c;
	int sockid,rval,clen,flag=0;
	char sym[20],ip[20],dnsfile[20],dnsname[20];
	FILE *fptr;
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
	printf("\nDNS server is waiting for file name");
	printf("\nEnter the DNS file name:");
	scanf("%s",dnsfile);
	fptr=fopen(dnsfile,"r");
	if(fptr==NULL){
		perror("\nError in file opening");
		exit(1);
	}
	clen=sizeof(c);
	rval=recvfrom(sockid,sym,sizeof(sym),0,(struct sockaddr *)&c,&clen);
	if(rval==-1){
		perror("\nERR_IN_RECV");
		exit(1);
	}
	printf("\nIP requested for %s",sym);
	while((fscanf(fptr,"%s%s",dnsname,ip)!=EOF)){
		if(strcmp(dnsname,sym)==0){
			rval=sendto(sockid,ip,sizeof(ip),0,(struct sockaddr *)&c,clen);
			if(rval==-1){
				perror("\nError in sending");
				exit(1);
			}
			flag=1;
		}
		printf("\nFlag value in the loop is %d",flag);
		if(flag==1)
			break;
	}
	if(flag==0){
		printf("\nInvalid domain name");
		rval=sendto(sockid,"Not Found",sizeof("Not Found"),0,(struct sockaddr *)&c,clen);
		if(rval==-1){
			perror("\nError in sending");
			exit(1);
		}
	}
	fclose(fptr);
	close(sockid);
}
