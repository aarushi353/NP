#include<sys/types.h> // contains data type definitions
#include<sys/socket.h> // contains data definitions for socket structures
#include<netdb.h> // contains data definitions for socket subroutines
#include<stdio.h>  
#include<string.h> 
#include<fcntl.h>
#include<unistd.h>

int main(){
    char str[100]; // 
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr; // for the purpose of specifying addresses
	unsigned int len;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); // Socket creation -> family, type, protocol

    bzero(&servaddr, sizeof(servaddr)); // acts like memset
    servaddr.sin_family = AF_INET; // internet protocol
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // internet address 32 bits
    servaddr.sin_port=htons(22000); //address port (16 bits)
    
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listen_fd, 10); // socket_id, queue limit    
	len = sizeof(servaddr);
    comm_fd = accept(listen_fd, (struct sockaddr*) &servaddr, &len);
    while(1){
        memset(&str, 0, sizeof(str));

        recv(comm_fd, str, 100, 0);
        // sock_id, recvBuf, bufLen, flags
        printf("Echoing back - %s", str);

        send(comm_fd, str, strlen(str), 0);
        // sock_id, msg, msgLen, flags
    }
	close(comm_fd);
	close(listen_fd);
}
