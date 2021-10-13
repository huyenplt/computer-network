#include "main_functions.h"

int main() {
    Node head = initHead();
    head = readFile(head);
    char signedIn_usrname[INFO_LENGTH];
    char choice;
    do {
        // system("cls");
        printf("\nUSER MANAGEMENT PROGRAM"); 
        printf("\n-------------------------\n");
        printf("\n1. Register");
        printf("\n2. Activate");
        printf("\n3. Sign in");
        printf("\n4. Search");
        printf("\n5. Change password");
        printf("\n6. Sign out");
        printf("\n\nYour choice (1-6, other to quit): ");
        scanf("%c", &choice);
        switch (choice) {
            case '1':
                printf("**** 1. Register ***\n\n");
                head = acc_register(head);
                break;
            case '2':
                printf("**** 2. Activate ***\n\n");
                head = activate_acc(head);
                break;
            case '3':
                printf("**** 3. Sign in ***\n\n");
                head = signIn(head, signedIn_usrname);
                break;
            case '4':
                printf("**** 4. Search ***\n\n");
                search_acc(head);
                break;
            case '5':
                printf("**** 5. Change password ***\n\n");
                head = changePwd(head, signedIn_usrname);
                break;
            case '6':
                printf("**** 6. Sign out ***\n\n");
                signOut(signedIn_usrname);
                break;
            default: 
                printf("Good bye!\n");
        }
    } while (choice > '0' && choice < '7');
}