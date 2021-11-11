#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "LinkedList.h"

// #define server_port 8080
#define BUFF_SIZE 512

int main(int argc, char *argv[])
{
    Node head = initHead();
    head = readFile(head);

    if (argc != 2) {
		printf("Invalid format!\nPlease enter follow format ./server port\n");
		return 0;
	}

    int server_port = atoi(argv[1]);
    int sockfd, rcvBytes, sendBytes;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    char username[BUFF_SIZE+1];
    char password[BUFF_SIZE+1];

    // Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error: ");
        return 0;
    }

    //Step 2: Bind address to socket
    // memset(&servaddr, 0, sizeof(servaddr));
    // memset(&cliaddr, 0, sizeof(cliaddr));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(server_port);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        perror("Error: ");
        return 0;
    }

    printf("Server started.\n");

    //Step 3: Communicate with client
    for (;;)
    {
        len = sizeof(cliaddr);
        rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0,
                            (struct sockaddr *)&cliaddr, &len);
        if (rcvBytes < 0)
        {
            perror("Error: ");
            return 0;
        }
        buff[rcvBytes] = '\0';
        // printf("%lu", strlen(username));
        printf("Client : %s\n", buff);

        if (strlen(buff) == 0) 
            return 0;


        if (!lookupByUsrname(head, buff)) {
            strcpy(buff, "Username not found! Please enter again\n");
        }
        else {
            strcpy(username, buff);
            strcpy(buff, "Please enter password");
        }

        // puts(buff);
        sendBytes = sendto(sockfd, buff, rcvBytes, 0,
                           (struct sockaddr *)&cliaddr, len);
        if (sendBytes < 0)
        {
            perror("Error: ");
            return 0;
        }
    }
    // len = sizeof(cliaddr); //len is value/resuslt

    // rcvBytes = recvfrom(sockfd, (char *)buff, BUFF_SIZE,
    //                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
    //                     &len);
    // buff[rcvBytes] = '\0';
    // printf("Client : %s\n", buff);
    // sendto(sockfd, (const char *)hello, strlen(hello),
    //        0, (const struct sockaddr *)&cliaddr,
    //        len);
    printf("Hello message sent.\n");

    return 0;
}