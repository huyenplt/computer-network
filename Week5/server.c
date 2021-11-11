#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "LinkedList.h"

#define MAXLINE 80

int isValidPasswordStr(char *pwdStr) {
    int i;
    for(i = 0; i < strlen(pwdStr); i++) {
        if (pwdStr[i] < 48 || (pwdStr[i] > 57 && pwdStr[i]< 65) || (pwdStr[i] > 90 && pwdStr[i] < 97) || pwdStr[i] > 122)
            return 0;
    }
    return 1;
}

int isValidPort(char *str) {
	int i;
	for(i = 0 ; i < strlen(str) ; i++) {
		if(str[i] < 48 || str[i] > 57) 
		     return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Invalid format!\nPlease enter follow format ./server port\n");
		return 0;
	}
	if (!isValidPort(argv[1])) {
		printf("Invalid port. Port must be digit. Please try again\n");
		return 0;
	}
	int server_port = atoi(argv[1]);

	int sockfd, connfd, n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t clilen;
	char buff[MAXLINE];

	Node head = initHead();
    head = readFile(head);

    Node tmp = NULL;
    int loginStatus = 0;
    int countWrongPwd;

	char username[MAXLINE + 1];
    char strDigit[MAXLINE + 1];
    char strAlpha[MAXLINE + 1];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(server_port);

	if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	
	for(;;) {
		connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
		if (connfd < 0) {
			printf("server accept failed...\n");
			exit(0);
		}
		else
			printf("server accept the client...\n");
		
		while((n = recv(connfd, buff, MAXLINE, 0)) > 0) {
			buff[n] = '\0';
			printf("From client: %s", buff);

			buff[strlen(buff) - 1] = '\0';

			if(strlen(buff) == 0) {
				printf("Server Exit...\n");
				return 0;
			}
			
			// Nhap username
			if (loginStatus == 0) {
				tmp = lookupByUsrname(head, buff);
				if (!tmp) {
					strcpy(buff, "Username not found. Please enter again!\n");
				}
				else {
					strcpy(username, buff);
					strcpy(buff, "Please enter password!\n");
					loginStatus = 1;
					countWrongPwd = 0;
				}
			}

			// Nhap password
			else if (loginStatus == 1) {
				if (strcmp(tmp->acc.password, buff) == 0)
					if (tmp->acc.status == 0 || tmp->acc.status == 2) {
						strcpy(buff, "Account is not ready. Please try another account!\n");
						loginStatus = 0;
					}
					else {
						strcpy(buff, "OK!\n\n Enter password to change:\n");
						loginStatus = 2;
					}
				else {
					countWrongPwd++;
					if(countWrongPwd == 3) {
						tmp->acc.status = 0;
						writeToFile(head);
						loginStatus = 0;
						strcpy(buff, "Account is blocked. Please try another account!\n");
					}
					else 
						strcpy(buff, "Not Ok! Wrong password!\n");
				}
			}

			// Nhap password de doi
			else {
				if (strcmp(buff, "bye") == 0) {
					strcpy(buff, "bye, ");
					strcpy(username, tmp->acc.username);
					username[strlen(username)] = '\n';
					strcat(buff, username);
					loginStatus = 0;
				}
				else {
					if (isValidPasswordStr(buff) == 0)
						strcpy(buff, "ERROR: Invalid password. Password must be alpha or digit\n");
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
							strAlpha[j + 1] = '\n';
							strDigit[k + 1] = '\n';

						}
						strcat(strAlpha, strDigit);
						strcpy(buff, "Password changed! Encode password: \n");
						strcat(buff, strAlpha);
						// strcat(buff, strDigit);

						writeToFile(head);
					}
				}
			}

			send(connfd, buff, n, 0);
		}
		
		if(n < 0) {
			perror("Read error");
			exit(1);
		}

		close(connfd);
	}

	close(sockfd);
}
