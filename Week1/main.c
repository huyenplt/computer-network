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
        fflush(stdin);
        scanf("%c", &choice);
        switch (choice) {
            case '1':
                printf("**** 1. Register ***\n\n");
                head = acc_register(head);
                printf("\nPress \"Enter\" key to continue.\n");
                fflush(stdin);
                getchar();
                break;
            case '2':
                printf("**** 2. Activate ***\n\n");
                head = activate_acc(head);
                printf("\nPress \"Enter\" key to continue.\n");
                fflush(stdin);
                getchar();
                break;
            case '3':
                printf("**** 3. Sign in ***\n\n");
                head = signIn(head, signedIn_usrname);
                printf("\nPress \"Enter\" key to continue.\n");
                fflush(stdin);
                getchar();
                break;
            case '4':
                printf("**** 4. Search ***\n\n");
                search_acc(head);
                printf("\nPress \"Enter\" key to continue.\n");
                fflush(stdin);
                getchar();
                break;
            case '5':
                printf("**** 5. Change password ***\n\n");
                head = changePwd(head, signedIn_usrname);
                printf("\nPress \"Enter\" key to continue.\n");
                fflush(stdin);
                getchar();
                break;
            case '6':
                printf("**** 6. Sign out ***\n\n");
                signOut(signedIn_usrname);
                printf("\nPress \"Enter\" key to continue.\n");
                fflush(stdin);
                getchar();
                break;
            default: 
                printf("Good bye!\n");
        }
    } while (choice > '0' && choice < '7');
}