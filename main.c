#include <stdio.h>
#include <stdbool.h> // for using bool

#include "auth.h"
#include "menu.h"
#include "config.h"

int main(){

    User currentUser; // logged will pass this to login function

    bool running = true;
    bool logged = false;

    while (running)
    {
        int failedLoginCounter = 0;
        while (!logged && running) // if  logged is false and if running is true --> go login
        {
            logged = login(&currentUser); // calls the login func from auth.c and passes the userName. This func returns true or false

            if(!logged) {
                //if failed to login 3 times stop the program
                failedLoginCounter++;

                printf("Attempts : %d\n", failedLoginCounter);

                if(failedLoginCounter >= MAX_ATTEMPTS) { // max MAX_ATTEMPTS is value given from config values as all other capital letter values
                    printf("Too many failed attempts!\n");
                    running = false; // it will close the program
                }
            }
        }

        while (logged) // if logged succesfully
        {
            int choice = showMenu(currentUser);// stores the choice returnted by showMenu()
            handleChoice(choice, currentUser, &logged, &running); //passes the choice made by showMenu to this function
                                                    //gives the addresses of logged and running so it can change it from the memory
        }       
    }
    return 0;
}