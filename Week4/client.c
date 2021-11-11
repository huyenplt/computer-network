#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFF_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid format!\nPlease enter follow format ./client IPAddress port\n");
        return 0;
    }

    int server_port = atoi(argv[2]);
    int sockfd, rcvBytes, sendBytes;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in servaddr;

    //Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error: ");
        return 0;
    }

    //Step 2: Define the address of the server
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //Step 3: Communicate with server
    printf("Send to server: \n");

    while (1) {
        gets(buff);
        len = sizeof(servaddr);
        sendBytes = sendto(sockfd, buff, strlen(buff), 0,
                           (struct sockaddr *)&servaddr, len);
        if(strlen(buff) == 0) return 0;
        if (sendBytes < 0)
        {
            perror("Error: ");
            return 0;
        }

        rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0,
                            (struct sockaddr *)&servaddr, &len);
        if (rcvBytes < 0)
        {
            perror("Error: ");
            return 0;
        }
        buff[rcvBytes] = '\0';
        printf("Reply from server: %s\n", buff);
    }
    return 0;
}