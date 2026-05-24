#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#include "user.h"
#include "config.h"
#include "auth.h"

const char* getRoleName(Role role)
{
    return role == ROLE_ADMIN ? "ADMIN" : "USER";
}

void addUser() {
    // adding user
    User newUser;

    printf("Username : ");
    scanf("%" USER_SCAN "s", newUser.userName);
    
    // CHECK IF USERNAME EXISTS
    if (userNameExists(newUser.userName))
    {
        printf("This user already exists!");
        return;
    }

    printf("Password : ");
    getPassword(newUser.password);

    newUser.role = ROLE_USER;

    FILE *file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    
    fprintf(file, "%s:%s:%d\n", newUser.userName, newUser.password, newUser.role); // adding user to file
    printf("\nAdded Username : %s\nAdded Password : %s\n", newUser.userName, newUser.password);
    fclose(file);
    printf("User added succesfully!\n");

    printf("\nPress any key...");
    _getch();

}

void editUser() {
    char userToEdit[MAX_USERNAME];
    char line[MAX_LINE];

    printf("Which user do you want to edit? : ");
    scanf("%" USER_SCAN "s", userToEdit);

    FILE *file = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }

    bool found = false;

    while (fgets(line, sizeof(line), file))
    {
        User fileUser;

        sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
        if (strcmp(userToEdit, fileUser.userName) == 0)
        {
            char approve;
            char newUserName[MAX_USERNAME];

            found = true;

            printf("New Username : ");
            scanf("%" USER_SCAN "s", newUserName);

            if (userNameExists(newUserName))
            {
                // username exists -> keep user
                fprintf(tempFile, "%s", line);
                printf("Username Already Exists!!\n");  
                continue;
            }
            

            printf("ARE YOU SURE ABOUT THE CHANGE Y/N ?   [%s] ---> [%s]\n", userToEdit, newUserName);
            scanf(" %c", &approve);

            // if approved -> add to the file
            if (approve == 'y' || approve == 'Y')
            {
                printf("Changed User : [%s] ---> [%s]\n", userToEdit, newUserName);
                fprintf(tempFile, "%s:%s:%d\n", newUserName, fileUser.password, fileUser.role);
            }
            else{
                // cancelled -> keep user
                fprintf(tempFile, "%s", line);
                printf("Cancelled!\n");
            }
        }

        else
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("User not found!");
        remove("temp.txt");
        return;
    }

    remove("users.txt");
    rename("temp.txt", "users.txt");

    printf("\nPress any key...");
    _getch();

    // basicly creates a temporary file and adds the edited user to this file with all other users and removes the original and changes the name of the temp file to original one :)

}

void deleteUser() {
    char userToDelete[MAX_USERNAME];
    char line[MAX_LINE];

    printf("Which user do you want to delete? : ");
    scanf("%" USER_SCAN "s", userToDelete);

    FILE *file = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }

    bool found = false;

    while (fgets(line, sizeof(line), file))// fgets reads a line from the file. fgets([where to store], [max size], [from which file])
    {
        User fileUser;

        sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
        if (strcmp(userToDelete, fileUser.userName) == 0)
        {
            char approve;
            found = true;

            printf("THIS USER WILL BE DELETED ARE YOU SURE Y/N?   [%s]\n", userToDelete);
            scanf(" %c", &approve);

            // if approved -> skip writing to temp file
            if (approve == 'y' || approve == 'Y')
            {
                printf("Deleted user : %s", userToDelete);
            }
            else{
                // cancelled -> keep user
                fprintf(tempFile, "%s", line);
                printf("Cancelled!\n");
            }
        }

        else
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("User not found!");
        remove("temp.txt");
        return;
    }

    remove("users.txt");
    rename("temp.txt", "users.txt");
    // basicly creates a temporary file and doesn't add the deleted user to this file 
    // but adds all other users and removes the original and changes the name of the temp file to original one :)

    printf("\nPress any key...");
    _getch();
}

void listUsers() { // just lists the whole file for usernames
    char line[MAX_LINE];
    
    FILE *file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        User fileUser;

        sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
        printf("%s [%s]\n", fileUser.userName, getRoleName(fileUser.role));
    }
    fclose(file);

    printf("\nPress any key...");
    _getch();

}

void searchUser() { // justs searches
    char line[MAX_LINE];
    char userToSearch[MAX_USERNAME];

    printf("Which user do you want to search? : ");
    scanf("%" USER_SCAN "s", userToSearch);

    FILE *file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    

    while (fgets(line, sizeof(line), file))// fgets reads a line from the file. fgets([where to store], [max size], [from which file])
    {
        User fileUser;

        sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
        if (strcmp(userToSearch, fileUser.userName) == 0)
        {
            printf("Found User : [%s] [%s]", fileUser.userName, getRoleName(fileUser.role));
        }
    }
    fclose(file);

    printf("\nPress any key...");
    _getch();
    
}