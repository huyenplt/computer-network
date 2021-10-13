#include "main_functions.h"

#define ACTIVATION_CODE "20184124"

int signedIn = 0;

void delChar(char s[], int position)
{
    int length = strlen(s);
    for (int i = position; i < length; i++)
        s[i] = s[i + 1];
    s[length - 1] = '\0';
}

void delSpace(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
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

// funtion 1 : Register
Node acc_register(Node head) {
    account newAcc;
    char usrname[INFO_LENGTH];
    char pwd[INFO_LENGTH];

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
    
    printf("Successful registration. Activation required.\n");
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
        printf("Enter username: ");
        fflush(stdin);
        gets(usrname);
        tmp = lookupByUsrname(head, usrname);
        if (!tmp)
            printf("Cannot find account. Try again!\n");

    } while (tmp == NULL);

    do
    {
        printf("Enter password: ");
        fflush(stdin);
        gets(pwd);
        if (strcmp(tmp->acc.password, pwd))
        {
            printf("Password is incorrect! Try again\n");
        }
    } while (strcmp(tmp->acc.password, pwd));

    do
    {
        printf("Enter activation code: ");
        fflush(stdin);
        gets(code);
        if (strcmp(code, ACTIVATION_CODE))
        {
            printf("Activation code is incorrect! Try again.\n");
            block_count++;
        }
    } while ((strcmp(code, ACTIVATION_CODE)) && (block_count <= 4));

    if (block_count >= 5)
    {
        printf("You've entered incorrect code more than 4 times. Account is blocked\n");
        tmp->acc.status = 0;
    }

    else
    {
        tmp->acc.status = 1;
        printf("Account is activated\n");
    }
    writeToFile(head);
    return head;
}

// function 3 : Sign in
Node signIn(Node head, char *usrname) {
    if (signedIn) {
        printf("You've already signed in! You have to sign out first!\n");
        return NULL;
    }

    char pwd[INFO_LENGTH];
    int block_count = 0;

    Node tmp = NULL;

    do
    {
        printf("Enter username: ");
        fflush(stdin);
        gets(usrname);
        tmp = lookupByUsrname(head, usrname);
        if (!tmp)
            printf("Cannot find account. Try again!\n");

    } while (tmp == NULL);

    do
    {
        printf("Enter password: ");
        fflush(stdin);
        gets(pwd);
        if (strcmp(tmp->acc.password, pwd))
        {
            printf("Password is incorrect! Try again\n");
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
        char usrname[INFO_LENGTH];
        char strStatus[8];
        Node tmp = NULL;

        do {
            printf("Enter username: ");
            fflush(stdin);
            gets(usrname);
            tmp = lookupByUsrname(head, usrname);
            if (!tmp)
                printf("Cannot find account. Try again!\n");

        } while (tmp == NULL);

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
        printf("You're not signed in. \nYou need to sign in first!\n");
        return NULL;
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
                printf("Password is incorrect! Try again\n");
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
            printf("Enter your username: ");
            fflush(stdin);
            gets(usrnameInput);
            if(strcmp(usrnameInput, usrname))
                printf("Incorrect username! Please try again!\n");
        } while (strcmp(usrnameInput, usrname));
        printf("Goodbye, %s!", usrname);
        signedIn = 0;
    }
}