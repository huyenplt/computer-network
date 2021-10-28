#include "LinkedList.h"

Node initHead(){
    Node head;
    head = NULL;
    return head;
}

Node createNode(account acc) {
    Node tmp;
    tmp = (Node)malloc(sizeof(struct LinkedList));
    tmp->next = NULL;
    tmp->acc = acc;
    return tmp;
}

Node addTail(Node head, account acc){
    Node temp, p; 
    temp = createNode(acc); 
    if(head == NULL){
        head = temp;     
    }
    else{
        p = head;
        while(p->next != NULL){
            p = p->next; 
        }
        p->next = temp; 
    }
    return head;
}

account createAcc(char *usrname, char *pwd, int status, char *homepage) {
    account newAcc;
    strcpy(newAcc.username, usrname);
    strcpy(newAcc.password, pwd);
    newAcc.status = status;
    strcpy(newAcc.homepage, homepage);

    return newAcc;
}

Node lookupByUsrname(Node head, char *username) {
    for(Node p = head; p != NULL; p = p->next){
        if (strcmp(p->acc.username, username) == 0)
            return p;
    }
    return NULL; 
}

void writeToFile(Node head) {
    FILE *fp = fopen("account.txt", "w");
    Node tmp = head;
    while (tmp != NULL) {
        account acc = tmp->acc;
        fprintf(fp, "%s %s %d %s\n", acc.username, acc.password, acc.status, acc.homepage);
        tmp = tmp->next;
    }
    fclose(fp);
}

Node readFile(Node head) {
    FILE* fp = fopen("account.txt", "r");
    char username[INFO_LENGTH];
    char password[INFO_LENGTH];
    int status;
    char homepage[50];
    while (!feof(fp)) {
        fscanf(fp, "%s %s %d %s\n", username, password, &status, homepage);
        account acc = createAcc(username, password, status, homepage);
        head = addTail(head, acc);
    }
    fclose(fp);
    return head;
}