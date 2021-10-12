#include "main_functions.h"

// funtion 1 : Register
Node acc_register(Node head){
    account newAcc;
    char usrname[30];
    char pwd[30];

    do {
        printf("Enter username: ");
        scanf("%s", usrname); 
        if (lookupByUsrname(head, usrname)) printf("Exit");
    } while (lookupByUsrname(head, usrname));
    


    printf("Enter password: ");
    scanf("%s", pwd);

    newAcc = createAcc(usrname, pwd, 2);
    head = addTail(head, newAcc);

    writeToFile(head); 

    return head;
}
