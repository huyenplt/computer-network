#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "LinkedList.h"

#define BUFF_SIZE 512

int isValidPasswordStr(char *pwdStr) {
    int i;
    for(i = 0; i < strlen(pwdStr); i++) {
        if (pwdStr[i] < 48 || (pwdStr[i] > 57 && pwdStr[i]< 65) || (pwdStr[i] > 90 && pwdStr[i] < 97) || pwdStr[i] > 122)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    Node head = initHead();
    head = readFile(head);

    Node tmp = NULL;
    int loginStatus = 0;
    int countWrongPwd = 0;

    if (argc != 2) {
		printf("Invalid format!\nPlease enter follow format ./server port\n");
		return 0;
	}

    int server_port = atoi(argv[1]);
    int sockfd, rcvBytes, sendBytes;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in servaddr, cliaddr;

    char username[BUFF_SIZE+1];
    char strDigit[BUFF_SIZE + 1];
    char strAlpha[BUFF_SIZE + 1];

    // Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error: ");
        return 0;
    }

    //Step 2: Bind address to socket
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(server_port);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        perror("Error: ");
        return 0;
    }

    printf("Server started.\n");

    //Step 3: Communicate with client
    for (;;) {
		memset(buff,'\0', BUFF_SIZE);
        len = sizeof(cliaddr);
        rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0,
                            (struct sockaddr *)&cliaddr, &len);
        if (rcvBytes < 0) {
            perror("Error: ");
            return 0;
        }
        buff[rcvBytes] = '\0';
        printf("Client : %s\n", buff);
        
        if (strlen(buff) == 0) 
            return 0;

        // Nhap username
        if (loginStatus == 0) {
            tmp = lookupByUsrname(head, buff);
            if (!tmp) {
                strcpy(buff, "Username not found. Please enter again!\n");
            }
            else {
                strcpy(username, buff);
                strcpy(buff, "Please enter password!");
                loginStatus = 1;
            }
        }
        // Nhap password
        else if (loginStatus == 1) {
            if (strcmp(tmp->acc.password, buff) == 0)
                if (tmp->acc.status == 0 || tmp->acc.status == 2) {
                    strcpy(buff, "Account is not ready. Please try another account!");
                    loginStatus = 0;
                }
                else {
                    strcpy(buff, "OK!\n\n Enter password to change: ");
                    loginStatus = 2;
                }
            else {
                countWrongPwd++;
                if(countWrongPwd == 3) {
                    tmp->acc.status = 0;
                    writeToFile(head);
                    loginStatus = 0;
                    strcpy(buff, "Account is blocked");
                }
                else 
                    strcpy(buff, "Not Ok! Wrong password!");
            }
        }

        // Nhap password de doi
        else {
            if (strcmp(buff, "bye") == 0) {
                strcpy(buff, "bye, ");
                strcat(buff, tmp->acc.username);
                loginStatus = 0;
            }
            else {
                if (isValidPasswordStr(buff) == 0)
                    strcpy(buff, "ERROR: Invalid password. Password must be alpha or digit");
                else {
                    strcpy(tmp->acc.password, buff);
                    memset(strAlpha, 0, sizeof(strAlpha));
	                memset(strDigit, 0, sizeof(strDigit));
                    int j = 0, k = 0;
                    for (int i = 0; i < strlen(buff); i++) {
                        if (isalpha(buff[i])) {
                            strAlpha[j] = buff[i];
                            j++;
                        }
                        else {
                            strDigit[k] = buff[i];
                            k++;
                        }
                    }
                    strcat(strAlpha, strDigit);
                    strcpy(buff, strAlpha);
                    writeToFile(head);
                }
            }
        }
       
        sendBytes = sendto(sockfd, buff, strlen(buff), 0,
                           (struct sockaddr *)&cliaddr, len);
        if (sendBytes < 0)
        {
            perror("Error: ");
            return 0;
        }
    }
    
    printf("Hello message sent.\n");

    return 0;
}