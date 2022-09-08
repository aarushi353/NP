#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFSIZE 32

int main(int argc, char *argv[]){
    int sock_fd;
    struct sockaddr_in sockAddr;
    char sendline[BUFSIZE];
    char recvline[BUFSIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd<0){
        printf("Error occured while creating slient socket.\n");
        exit(EXIT_FAILURE);
    }
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(8080);
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int status = connect(sock_fd, (struct sockaddr *) &sockAddr, sizeof(sockAddr));
    if(status<0)
	{
		printf("Error while connecting to the server.\n");
		exit(EXIT_FAILURE);
	}

    while(1){
        memset(&sendline, 0, BUFSIZE);
        memset(&recvline, 0, BUFSIZE);
        printf("Enter message: ");
        fgets(sendline, BUFSIZE, stdin);
        if(send(sock_fd, sendline, strlen(sendline), 0)<0){
            printf("Error while sending message.\n");
            exit(EXIT_FAILURE);
        }
        if(strcmp(sendline, "quit") == 0){
            break;
        }
        if(recv(sock_fd, recvline, BUFSIZE, 0)<0){
            printf("Error while receiving message.\n");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", recvline);
    }
    close(sock_fd);
    printf("Connection terminated and socket closed.\n");
}

