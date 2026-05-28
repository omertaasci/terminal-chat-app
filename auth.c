#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>

#include "auth.h"
#include "user.h"
#include "config.h"

bool userNameExists(char userName[]) { // this function checks if the username already exists
    FILE *file; // declaring the file
    char line[MAX_LINE]; // this string stores one line from the file temporarily for example first stores 1st line admin:31 then changes to 2nd line test:31 etc

    file = fopen("users.txt", "r"); // opening users.txt with read permission

    if (file == NULL) // if file is empty return false
    {
        return false;
    }

    while (fgets(line, sizeof(line), file)) // fgets reads a line from the file. fgets([where to store], [max size], [from which file])
    {
        User fileUser;

        sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
        if (strcmp(userName, fileUser.userName) == 0) // if username is matching with any username from the file which is fileUser
        {
            fclose(file);
            return true; // returns true which means that username exists
        }
        
    }

    fclose(file);
    return false; // returns false if not matched
}

// PASSWORD
bool checkPassword(char userName[], char userPassword[]) { // checks if the password is correct
    FILE *file; 
    char line[MAX_LINE]; // stores the readed line from the file

    file = fopen("users.txt", "r"); // opens file with read permission

    if (file == NULL) // if empty return false
    {
        return false;
    }

    while (fgets(line, sizeof(line), file)) { // fgets reads a line from the file. fgets([where to store], [max size], [from which file]);
        User fileUser;

        sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
        // sscanf reads the data from text
        // [^:] means read until ':'
        // USER_SCAN and PASS_SCAN is the limit for scanning which is -1 from the normal limit(20)
        // because last character needs to be \0 
        // sscanf([which string],[according to what format],[where to store the username value],[where to store password value]);

        if (strcmp(userName, fileUser.userName) == 0 && strcmp(userPassword, fileUser.password) == 0) // strcmp means string compare
        {
            fclose(file);
            return true; // if matches returns true
        }

    }
    fclose(file);
    return false; // if doesn't match returns false
}

//GET PASSWORD
void getPassword(char password[]) { // function for getting password
    int i = 0;
    char ch;

    while((ch = _getch()) != '\r') { // writes every character to the ch until pressed enter('\r')
        if(ch == '\b' && i > 0) { // if pressed backspace'\b' and index is not 0 
            i--; // decrease the index
            printf("\b \b"); // removes the last '*' from the screen
        }
        else if(i < MAX_PASSWORD - 1) { // bc last character will be '\0' we need to make sure its less than 19 because its password[20]
            password[i++] = ch; // assings the character from ch to the password
            printf("*"); // prints *
        }
    }

    password[i] = '\0'; // puts '\0' so it can understand where the string ends
}

// LOGIN
bool login(User *currentUser) {

    char password[MAX_PASSWORD];

    system("cls");
    
    printf("Username : ");
    //scanf("%" USER_SCAN "s", currentUser->userName); // %USER_SCANs makes sure its until 19 bc max is [20] and last will be '\0'
    fgets(currentUser->userName, sizeof(currentUser->userName), stdin);
    currentUser->userName[strcspn(currentUser->userName, "\n")] = '\0';

    if (!userNameExists(currentUser->userName))
    {
        printf("Username doest not exists!\n");
        return false;
    }
    
    printf("Password : ");
    getPassword(password); // calls getPassword() and stores the typed password into password string

    if (checkPassword(currentUser->userName, password))
    {
        FILE *file = fopen("users.txt", "r");
        char line[MAX_LINE]; // stores the readed line from the file

        while (fgets(line, sizeof(line), file)) { // fgets reads a line from the file. fgets([where to store], [max size], [from which file]);
            User fileUser;

            sscanf(line, "%" USER_SCAN "[^:]:%" PASS_SCAN "[^:]:%d", fileUser.userName, fileUser.password, &fileUser.role); // scans the file for the user
            // sscanf reads the data from text
            // [^:] means read until ':'
            // USER_SCAN and PASS_SCAN is the limit for scanning which is -1 from the normal limit(20)
            // because last character needs to be \0 
            // sscanf([which string],[according to what format],[where to store the username value],[where to store password value]);

            if (strcmp(currentUser->userName, fileUser.userName) == 0) // strcmp means string compare
            {
                currentUser->role = fileUser.role;
            }
        }

        fclose(file);

        printf("\nWelcome, %s [%s]", currentUser->userName, getRoleName(currentUser->role));
        printf("\nPress any key...");
        _getch();
        return true;
    }
    
    printf("\nIncorrect password!");
    printf("\nPress any key...");
    _getch();
    return false;
    
}
