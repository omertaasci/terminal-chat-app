#ifndef USER_H
#define USER_H

#include "config.h"

typedef struct 
{
    char userName[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[10];
} User;


void addUser();
void deleteUser();
void editUser();
void listUsers();
void searchUser();


#endif