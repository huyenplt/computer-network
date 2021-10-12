#include "main_functions.h"

// funtion 1 : Register
Node acc_register(Node head){
    account newAcc;
    char usrname[30];
    char pwd[30];

    do {
        printf("Enter username: ");
        fflush(stdin);
        gets(usrname); 
        if (lookupByUsrname(head, usrname)) 
            printf("Account existed. Please enter again! \n");
        if (strchr(usrname, ' ')) 
            printf("Invalid username. Pleasr enter again! \n");
    } while (lookupByUsrname(head, usrname) || strchr(usrname, ' '));
    
    printf("Enter password: ");
    fflush(stdin);
    scanf("%s", pwd);

    newAcc = createAcc(usrname, pwd, 2);
    head = addTail(head, newAcc);

    writeToFile(head);

    return head;
}
