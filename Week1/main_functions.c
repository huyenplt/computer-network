#include "main_functions.h"

#define ACTIVATION_CODE "20184124"

int signedIn = 0;

void delChar(char s[], int position) {
	int length = strlen(s);
    for(int i = position; i < length; i++)
        s[i] = s[i+1];
	s[length - 1] = '\0'; 
}

void delSpace(char *s) {
    for(int i = 0; i < strlen(s); i++) {
		if(s[i] == ' ' && s[i+1] == ' ') {
			delChar(s, i);
			i--;
		}
    }
    if(s[0] == ' ')
		delChar(s, 0); // xoá đầu

    if(s[strlen(s)-1] == ' ')
		delChar(s, strlen(s)-1); // xoá cuối
}

// funtion 1 : Register
Node acc_register(Node head){
    account newAcc;
    char usrname[30];
    char pwd[30];

    do {
        printf("Enter username: ");
        fflush(stdin);
        gets(usrname);
        delSpace(usrname);
        if (lookupByUsrname(head, usrname)) 
            printf("Account existed. Please enter again! \n");
        if (strchr(usrname, ' ')) 
            printf("Invalid username. Pleasr enter again! \n");
    } while (lookupByUsrname(head, usrname) || strchr(usrname, ' '));
    
    printf("Enter password: ");
    fflush(stdin);
    gets(pwd);

    newAcc = createAcc(usrname, pwd, 2);
    head = addTail(head, newAcc);

    writeToFile(head);

    return head;
}


// existed account
Node existedAcc(Node head) {
    char usrname[30];
    Node tmp = NULL;

    do {
        printf("Enter username: ");
        fflush(stdin);
        gets(usrname);
        tmp = lookupByUsrname(head, usrname);
        if (!tmp)
            printf("Cannot find account. Try again!\n");

    } while (tmp == NULL);

    return tmp;
}

// function 2 : Activate account
Node activate_acc(Node head) {
    char pwd[30];
    char code[8];
    int block_count = 0;

    Node tmp = existedAcc(head);

    do {
        printf("Enter password: ");
        fflush(stdin);
        gets(pwd);
        if(strcmp(tmp->acc.password, pwd)) {
            printf("Password is incorrect! Try again\n");
        }
    } while (strcmp(tmp->acc.password, pwd));

    do {
        printf("Enter activation code: ");
        fflush(stdin);
        gets(code);
        if(strcmp(code, ACTIVATION_CODE)) {
            printf("Activation code is incorrect! Try again.\n");
            block_count++;
        }
    } while ((strcmp(code, ACTIVATION_CODE)) && (block_count <= 4));

    if (block_count >= 5) {
        printf("You've entered incorrect code more than 4 times. Account is blocked\n");
        tmp->acc.status = 0; 
    }

    else {
        tmp->acc.status = 1;
        printf("Account is activated\n");
    }
    writeToFile(head);
    return head;
}

// function 3 : Sign in
Node signIn(Node head) {
    char pwd[30];
    int block_count = 0;

    Node tmp = existedAcc(head);

    do {
        printf("Enter password: ");
        fflush(stdin);
        gets(pwd);
        if(strcmp(tmp->acc.password, pwd)) {
            printf("Password is incorrect! Try again\n");
            block_count++;
        }
    } while (strcmp(tmp->acc.password, pwd) && (block_count <= 3));

    if (block_count >= 4) {
        printf("You've entered incorrect password more than 3 times. Account is blocked\n");
        tmp->acc.status = 0; 
        writeToFile(head);
    }
    
    else {
        printf("Logged in successfully!\nHi, %s!", tmp->acc.username);
        signedIn = 1;
    }
    return head;
}

// Function 4: Search
void search_acc(Node head) {
    if (!signedIn) 
        printf("You're not signed in. \nYou need to sign in first!\n");
    else {
        Node tmp = existedAcc(head);
        printf("Account found!\n");
        printf("Username: %s\nStatus: %d\n", tmp->acc.username, tmp->acc.status);
    }
}

