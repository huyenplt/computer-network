#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int isIPAdrr(char* param2) {
    char *string;
    strcpy(string, param2);
    char *token;
    int count = 0;
    token = strtok(string, ".");

    while (token) {
        if(atoi(token) < 0 || atoi(token) > 255)
            return 0;

        token = strtok(NULL, ".");

        count++;
    }
    if(count != 4) 
        return 0;
    
    return 1;
}

int main(int argc, char** argv) {
    struct hostent *host;
    struct in_addr in;
    struct sockaddr_in addr_in;

    char param1[2];
    char param2[50];
    strcpy(param1, argv[1]);
    strcpy(param2, argv[2]);

    if(!strcmp(param1, "1")) {
        if(!isIPAdrr(param2)) {
            printf("Wrong parameter\n");
            return 0;
        }
    
        inet_aton(param2, &in);
        host = gethostbyaddr(&in, sizeof(in), AF_INET);
        if(host) {
            printf("\n---------------------\n");
            printf("Domain name : %s \n",host->h_name);
            int i = 0;
            if(host->h_aliases[i]) 
                printf("Alias name: \n");
            while (host->h_aliases[i]) {
                printf("\t%s\n",host->h_aliases[i]);
                i++;
            }
        }
        else 
            printf("Not found information\n");
        return 0;
    }

    else if(!strcmp(param1, "2")) {
        if(isIPAdrr(param2)) {
            printf("Wrong parameter\n");
            return 0;
        }

        host = gethostbyname(param2);
        if(host) {
            printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
            int i = 1;
            if(host->h_addr_list[i]) 
                printf("Alias IP: \n");
            while (host->h_addr_list[i]) {
                printf("\t%s\n",host->h_addr_list[i]);
                i++;
            }
        }
        else 
            printf("Not found information\n");
    }
    else
        printf("Wrong parameter\n");
}