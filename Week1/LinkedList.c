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

account createAcc(char *usrname, char *pwd, int status) {
    account newAcc;
    strcpy(newAcc.username, usrname);
    strcpy(newAcc.password, pwd);
    newAcc.status = status;

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
        fprintf(fp, "%s %s %d\n", acc.username, acc.password, acc.status);
        tmp = tmp->next;
    }
    fclose(fp);
}

Node readFile(Node head) {
    FILE* fp = fopen("account.txt", "r");
    char username[30];
    char password[30];
    int status;
    while (!feof(fp)) {
        fscanf(fp, "%s %s %d\n", username, password, &status);
        account acc = createAcc(username, password, status);
        head = addTail(head, acc);
    }
    fclose(fp);
    return head;
}