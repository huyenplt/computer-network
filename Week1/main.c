#include <stdio.h>
#include <stdlib.h>
#include "main_functions.h"

int main() {
    Node head = initHead();
    head = readFile(head);
    int choice;
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
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("**** 1. Register ***\n\n");

                head = acc_register(head);
                // for(Node p = head; p != NULL; p = p->next){
                //     printf("%s\n", p->acc.username);
                // }
                break;
            case 2:
                printf("**** 2. Activate ***\n\n");
                head = activate_acc(head);
                break;
            case 3:
                printf("**** 3. Sign in ***\n\n");
                head = signIn(head);
                break;
            case 4:
                printf("**** 4. Search ***\n\n");
                search_acc(head);
                break;
            case 5:
                printf("**** 5. Change password ***\n\n");
                break;
            case 6:
                printf("**** 6. Sign out ***\n\n");
                break;
            default: 
                printf("hihi\n");
        }
    } while (choice > 0 && choice < 7);
}