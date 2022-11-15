#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
struct sockaddr_in servaddr, cliaddr;
char msg[100]={"THIS IS A BROADCAST MESSAGE"};
int x=1;
void main()
{
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);	
	if(sockfd<0)
	{
		printf("Creation Failed!");
		exit(0);
	}
	else
		printf("Creation Successful!");
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(50000);
	servaddr.sin_addr.s_addr=inet_addr("10.0.2.255");
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&x,sizeof(x));
	sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	close(sockfd);
}
