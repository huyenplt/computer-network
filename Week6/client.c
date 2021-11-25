#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAXLINE 80

int isValidPort(char *str) {
	int i;
	for(i = 0 ; i < strlen(str) ; i++) {
		if(str[i] < 48 || str[i] > 57) 
		     return 0;
	}
	return 1;
}

int isValidIpAddr(char *str)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, str, &(sa.sin_addr));
    if (result != 0)
        return 1;
    return 0;
}

void func(int sockfd) {
	char buff[MAXLINE];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		if (strlen(buff) == 1) {
			printf("Client Exit...\n");
			write(sockfd, buff, sizeof(buff));
			break;
		}
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
        printf("Invalid format!\nPlease enter follow format ./client IPAddress port\n");
        return 0;
    }

	if(!isValidIpAddr(argv[1])) {
        printf("Invalid Address! Please try again\n");
        return 0;
    }

	if (!isValidPort(argv[2])) {
		printf("Invalid port. Port must be digit. Please try again\n");
		return 0;
	}
	int server_port = atoi(argv[2]);
	
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(server_port);

	// connect the client socket to server socket
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
