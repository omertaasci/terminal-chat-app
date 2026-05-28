#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "menu.h"
#include "user.h"
#include "chat.h"

int showMenu(User currentUser) { // basicly returns the choice as int
    char input[32];
    int choice;

    bool isAdmin = currentUser.role == ROLE_ADMIN;
    
    system("cls");

    if (isAdmin)
    {
        printf("\n====== MENU ======\n");
        printf("1 - Add User [ADMIN MODE]\n");
        printf("2 - Edit User [ADMIN MODE]\n");
        printf("3 - Delete User [ADMIN MODE]\n");
        printf("4 - Join Public Chat\n");
        printf("5 - List Users\n");
        printf("6 - Search User\n");
        printf("7 - Logout\n");
        printf("8 - Exit Program\n");
        printf("Choice : ");

        //scanf("%d", &choice);
        //printf("choice memory location : %p\n", (void*)&choice);

        fgets(input, sizeof(input), stdin);
        choice = (int)strtol(input, NULL, 10);
        
        return choice; 
    }
    else
    {
        printf("\n====== MENU ======\n");
        printf("1 - Join Public Chat\n");
        printf("2 - List Users\n");
        printf("3 - Search User\n");
        printf("4 - Logout\n");
        printf("5 - Exit Program\n");
        printf("Choice : ");

        //scanf("%d", &choice);
        //printf("choice memory location : %p\n", (void*)&choice);

        fgets(input, sizeof(input), stdin);

        choice = (int)strtol(input, NULL, 10); // converts string input to int choice

        return choice;
    }
    
}


void handleChoice(int choice, User currentUser, bool *logged, bool *running) {
    bool isAdmin = currentUser.role == ROLE_ADMIN;

    if (isAdmin)
    {
        switch (choice)
        {
            case 1:
                system("cls");
                printf("Add User [ADMIN MODE]\n");
                addUser();
                break;

            case 2:
                system("cls");
                printf("Edit User [ADMIN MODE]\n");
                editUser();
                break;

            case 3:
                system("cls");
                printf("Delete User [ADMIN MODE]\n");
                deleteUser();
                break;
            case 4:
                system("cls");
                printf("\n==== Public Chat ====\n\n");
                joinChat(currentUser);
                break;
            case 5:
                system("cls");
                printf("\n==== USER LIST ====\n\n");
                listUsers();
                break;

            case 6:
                system("cls");
                printf("\n==== SEARCH USER ====\n\n");
                searchUser();
                break;

            case 7:
                system("cls");
                printf("Logged out\n");
                *logged = false; // changes the original variable in the memory
                printf("\nPress any key...");
                _getch();
                break;

            case 8:
                system("cls");
                printf("Program Closed\n");
                *running = false; // changes the original variable in the memory 
                *logged = false; // changes the original variable in the memory 
                break;

            default:
                printf("Invalid choice!\n");

                printf("\nPress any key...");
                _getch();
        }
    }
    else
    {
        switch (choice)
        {
            case 1:
                system("cls");
                printf("\n==== Public Chat ====\n\n");
                joinChat(currentUser);
                break;
            case 2:
                system("cls");
                printf("\n==== USER LIST ====\n\n");
                listUsers();
                break;

            case 3:
                system("cls");
                printf("\n==== SEARCH USER ====\n\n");
                searchUser();
                break;

            case 4:
                system("cls");
                printf("Logged out\n");
                *logged = false; // changes the original variable in the memory
                break;

            case 5:
                system("cls");
                printf("Program Closed\n");
                *running = false; // changes the original variable in the memory 
                *logged = false; // changes the original variable in the memory 
                break;

            default:
                printf("Invalid choice!\n");
        }
    }
    
}