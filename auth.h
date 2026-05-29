#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>
#include "user.h"

void writeLog(const char *message, const char *userName);
bool login(User *currentUser);
bool userNameExists(char userName[]);
bool checkPassword(char userName[], char userPassword[]);
void getPassword(char password[]);

#endif