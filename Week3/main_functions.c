#include "main_functions.h"
#include <netdb.h>
#include <arpa/inet.h>

#define ACTIVATION_CODE "20184124"

int signedIn = 0;

void delChar(char s[], int position) {
    int length = strlen(s);
    for (int i = position; i < length; i++)
        s[i] = s[i + 1];
    s[length - 1] = '\0';
}

void delSpace(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ' && s[i + 1] == ' ')
        {
            delChar(s, i);
            i--;
        }
    }
    if (s[0] == ' ')
        delChar(s, 0); // xoá đầu

    if (s[strlen(s) - 1] == ' ')
        delChar(s, strlen(s) - 1); // xoá cuối
}

int isValidHomepageStr(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ')
            return 0;
    }
    return 1;
}

int isIPAdrr(char* str) {
    char string[50];
    strcpy(string, str);
    char *token;
    // int count = 0;
    token = strtok(string, ".");

    while (token) {
        if(atoi(token) == 0)
            return 0;

        token = strtok(NULL, ".");
    }
    
    return 1;
}

// funtion 1 : Register
Node acc_register(Node head) {
    account newAcc;
    char usrname[INFO_LENGTH];
    char pwd[INFO_LENGTH];
    char homepage[50];

    do {
        printf("\nEnter username: ");
        fflush(stdin);
        gets(usrname);
        delSpace(usrname);
        if (lookupByUsrname(head, usrname))
            printf("Account existed. Please enter again!\n");
        if (strchr(usrname, ' '))
            printf("Invalid username. Please enter again!\n");
    } while (lookupByUsrname(head, usrname) || strchr(usrname, ' '));

    printf("Enter password: ");
    fflush(stdin);
    gets(pwd);

    do {
        printf("Enter homepage: ");
        fflush(stdin);
        gets(homepage);
        if(!isValidHomepageStr(homepage))
            printf("Invalid homepage. Please enter again!\n");
    } while (!isValidHomepageStr(homepage));
    

    newAcc = createAcc(usrname, pwd, 2, homepage);
    head = addTail(head, newAcc);
    
    printf("\nSuccessful registration. Activation required.\n");
    writeToFile(head);

    return head;
}

// function 2 : Activate account
Node activate_acc(Node head)
{
    char usrname[INFO_LENGTH];
    char pwd[INFO_LENGTH];
    char code[8];
    int block_count = 0;

    Node tmp = NULL;

    do
    {
        printf("\nEnter username: ");
        fflush(stdin);
        gets(usrname);
        tmp = lookupByUsrname(head, usrname);
        if (!tmp)
            printf("\nCannot find account. Please try again!\n");

    } while (tmp == NULL);

    do
    {
        printf("Enter password: ");
        fflush(stdin);
        gets(pwd);
        if (strcmp(tmp->acc.password, pwd))
        {
            printf("\nPassword is incorrect! Please try again\n");
        }
    } while (strcmp(tmp->acc.password, pwd));

    do
    {
        printf("Enter activation code: ");
        fflush(stdin);
        gets(code);
        if (strcmp(code, ACTIVATION_CODE))
        {
            printf("\nActivation code is incorrect! Please try again.\n");
            block_count++;
        }
    } while ((strcmp(code, ACTIVATION_CODE)) && (block_count <= 4));

    if (block_count >= 5)
    {
        printf("\nYou've entered incorrect code more than 4 times. Account is blocked\n");
        tmp->acc.status = 0;
    }

    else
    {
        tmp->acc.status = 1;
        printf("\nAccount is activated!\n");
    }
    writeToFile(head);
    return head;
}

// function 3 : Sign in
Node signIn(Node head, char *usrname) {
    if (signedIn) {
        printf("\nYou've already signed in! You have to sign out first!\n");
        return head;
    }

    char pwd[INFO_LENGTH];
    int block_count = 0;

    Node tmp = NULL;

    do
    {
        printf("\nEnter username: ");
        fflush(stdin);
        gets(usrname);
        tmp = lookupByUsrname(head, usrname);
        if (!tmp)
            printf("\nCannot find account. Please try again!\n");

    } while (tmp == NULL);

    do
    {
        printf("Enter password: ");
        fflush(stdin);
        gets(pwd);
        if (strcmp(tmp->acc.password, pwd))
        {
            printf("Password is incorrect! Please try again\n");
            block_count++;
        }
    } while (strcmp(tmp->acc.password, pwd) && (block_count <= 3));

    if (block_count >= 4)
    {
        printf("You've entered incorrect password more than 3 times. Account is blocked\n");
        tmp->acc.status = 0;
        writeToFile(head);
    }

    else
    {
        printf("Logged in successfully!\nHi, %s!\n", tmp->acc.username);
        signedIn = 1;
    }
    return head;
}

// Function 4: Search
void search_acc(Node head) {
    if (!signedIn)
        printf("You're not signed in. \nYou need to sign in first!\n");

    else {
        char usrname[INFO_LENGTH];
        char strStatus[8];
        Node tmp = NULL;

        do {
            printf("Enter username: ");
            fflush(stdin);
            gets(usrname);
            tmp = lookupByUsrname(head, usrname);
            if (!tmp)
                printf("Cannot find account. Please try again!\n");

        } while (tmp == NULL);

        printf("%s\n", tmp->acc.homepage);

        switch (tmp->acc.status) {
        case 0:
            strcpy(strStatus, "blocked");
            break;
        case 1: 
            strcpy(strStatus, "active");
            break;
        case 2: 
            strcpy(strStatus, "idle");
            break;
        default:
            break;
        }

        printf("Account found!\n");
        printf("Account '%s' is %s\n", tmp->acc.username, strStatus);
    }
}

// Function 5: Change password
Node changePwd(Node head, char *usrname) {
    if (!signedIn) {
        printf("\nYou're not signed in. \nYou need to sign in first!\n");
        return head;
    }
    else {
        char pwd[INFO_LENGTH];
        char newPwd[INFO_LENGTH];

        Node tmp = lookupByUsrname(head, usrname);

        printf("Hi, %s. You have to enter your password to change!\n", usrname);

        do {
            printf("Enter password: ");
            fflush(stdin);
            gets(pwd);
            if (strcmp(tmp->acc.password, pwd)) 
                printf("Password is incorrect! Please try again\n");
        } while (strcmp(tmp->acc.password, pwd));

        printf("Enter new password: ");
        fflush(stdin);
        gets(newPwd);
        strcpy(tmp->acc.password, newPwd);
        writeToFile(head);
        printf("Password is changed!\n");
        return head;
    }
}

// Function 6: sign out
void signOut(char *usrname) {
    if (!signedIn) {
        printf("You're not signed in. \nYou need to sign in first!\n");
    }
    else {
        char usrnameInput[INFO_LENGTH];
        do {
            printf("\nEnter your username: ");
            fflush(stdin);
            gets(usrnameInput);
            if(strcmp(usrnameInput, usrname))
                printf("Incorrect username! Please try again!\n");
        } while (strcmp(usrnameInput, usrname));
        printf("\nGoodbye, %s!\n", usrname);
        signedIn = 0;
    }
}

struct hostent *host;
struct in_addr in;
struct sockaddr_in addr_in;

// Function 7: home page with domain name
void getDomainName(Node head, char *usrname) {
    if (!signedIn) {
        printf("\nYou're not signed in. \nYou need to sign in first!\n");
    }
    else {
        char str[50];
        Node tmp = lookupByUsrname(head, usrname);
        printf("\nHomepage: %s\n", tmp->acc.homepage);
        strcpy(str, tmp->acc.homepage);

        if (isIPAdrr(str)) {
            inet_aton(str, &in);
            host = gethostbyaddr(&in, sizeof(in), AF_INET);
        }
        else 
            host = gethostbyname(str);

        if(host) {
            printf("------\n");
            printf("Domain name : %s \n", host->h_name);
            int i = 0;
            if(host->h_aliases[i]) 
                printf("Alias name: \n");
            while (host->h_aliases[i]) {
                printf("\t%s\n", host->h_aliases[i]);
                i++;
            }
        }
        else 
            printf("Not found information\n");
    }
}

// Function 7: home page with domain name
void getIPAddr(Node head, char *usrname) {
    if (!signedIn) {
        printf("\nYou're not signed in. \nYou need to sign in first!\n");
    }
    else {
        char str[50];
        Node tmp = lookupByUsrname(head, usrname);
        printf("\nHomepage: %s\n", tmp->acc.homepage);
        strcpy(str, tmp->acc.homepage);

        if (isIPAdrr(str)) {
            inet_aton(str, &in);
            host = gethostbyaddr(&in, sizeof(in), AF_INET);
        }
        else 
            host = gethostbyname(str);

        if(host) {
            printf("------\n");
            printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
            int i = 1;
            if(host->h_addr_list[i]) 
                printf("Alias IP: \n");
            while (host->h_addr_list[i]) {
                printf("\t%s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
                i++;
            }
        }
        else 
            printf("Not found information\n");
    }
}