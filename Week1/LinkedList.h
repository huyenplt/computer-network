#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char username[30];
    char password[30];
    int status;
};
typedef struct Account account;

struct LinkedList {
    account acc;
    struct LinkedList *next;
};
typedef struct LinkedList *Node;

Node initHead();
Node createNode(account acc);
account createAcc(char *usrname, char *pwd, int status);
Node addTail(Node head, account acc);
Node lookupByUsrname(Node head, char *username);
void writeToFile(Node head);
Node readFile(Node head);

