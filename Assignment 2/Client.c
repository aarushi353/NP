#include<sys/types.h> // contains data type definitions
#include<sys/socket.h> // contains data definitions for socket structures
#include<netdb.h> // contains data definitions for socket subroutines
#include<stdio.h>  
#include<string.h> 
#include<fcntl.h>
#include<arpa/inet.h>

int main(int argc, char **argv){
    int sock_fd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    sock_fd=socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);

    servaddr.sin_port = htons(22000);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd,(struct sockaddr *)&servaddr, sizeof(servaddr));

    while(1){
    memset(&sendline, 0, sizeof(sendline));
    memset(&recvline, 0, sizeof(recvline));
    fgets(sendline, 100, stdin); /* stdin=0, for standard input */
    
    send(sock_fd, sendline, strlen(sendline),0);
    recv(sock_fd, recvline, 100, 0);

    printf("%s", recvline);

    }
}
