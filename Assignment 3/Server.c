#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 10
#define RCVBUFSIZE 32
#define PORT 8080
int main()
{
	int servSock;
	int clntSock;
	struct sockaddr_in ServAddr;
	struct sockaddr_in ClntAddr;
	unsigned short ServPort;
	unsigned int clntLen;

	ServPort = PORT;

	// Initializing server socket
	printf("Creating Server Socket...\n");
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock < 0)
	{
		printf("Error while creating socket.");
	}
	printf("Server Socket Successfully Created.\n");

	// Configuring server socket
	printf("Configuring server socket...\n");
	memset(&ClntAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(ServPort);

	// Binding Configuration
	int status = bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr));
	if (status < 0)
	{
		printf("Error while binding configuration to the socket.\n");
		exit(EXIT_FAILURE);
	}
	printf("Configuration of server socket completed.\n");

	// Make the socket listen for incoming connections
	status = listen(servSock, MAXPENDING);
	if (status < 0)
	{
		printf("Error while trying to make socket listen for active connections.\n");
		exit(EXIT_FAILURE);
	}
	printf("Socket is now listening for active connections!\n");

	// Declare variables for receiving message
	char recvMsgBuffer[RCVBUFSIZE];
	char sendMsgBuffer[RCVBUFSIZE];
	int sendMsgSize;
	int recvMsgSize;
	for (;;) // Infinite loop
	{
		memset(&ClntAddr, 0, sizeof(ClntAddr));
		clntLen = sizeof(ClntAddr);

		// Connect with client
		printf("Waiting for client to connect...");
		clntSock = accept(servSock, (struct sockaddr *) &ClntAddr, &clntLen);
		if (clntSock < 0)
		{
			printf("Error while connecting with client.\n");
			exit(EXIT_FAILURE);
		}
		printf("Successfully connected with client!\n");

		for (;;)
		{
			memset(&sendMsgBuffer, 0, RCVBUFSIZE);
			memset(&recvMsgBuffer, 0, RCVBUFSIZE);
			recvMsgSize = recv(clntSock, recvMsgBuffer, RCVBUFSIZE, 0);
			if (recvMsgSize < 0)
			{
				printf("Error while receiving message.\n");
				exit(EXIT_FAILURE);
			}
			printf("%s\nSend Message: ", recvMsgBuffer);

			fgets(sendMsgBuffer, RCVBUFSIZE, stdin);
		
			if (strcmp(sendMsgBuffer, "quit")==0)
			{
				break;
			}

			sendMsgSize = send(clntSock, sendMsgBuffer, RCVBUFSIZE, 0);
			if (sendMsgSize < 0)
			{
				printf("Error while sending the message.\n");
				exit(EXIT_FAILURE);
			}
		}
		close(clntSock);
		break;
	}
	close(servSock);
	printf("Connection terminated and server closed.\n");
}
