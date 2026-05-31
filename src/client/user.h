#ifndef USER_H
#define USER_H

#include "config.h"

typedef enum
{
    ROLE_USER,
    ROLE_ADMIN
} Role;

typedef struct 
{
    char userName[MAX_USERNAME];
    char password[MAX_PASSWORD];
    Role role;
} User;


void addUser();
void deleteUser();
void editUser();
void listUsers();
void searchUser();

const char* getRoleName(Role role);

#endif