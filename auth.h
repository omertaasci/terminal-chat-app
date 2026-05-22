#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>
#include "user.h"

bool login(User *currentUser);
bool userNameExists(char userName[]);
bool checkPassword(char userName[], char userPassword[]);
void getPassword(char password[]);

#endif