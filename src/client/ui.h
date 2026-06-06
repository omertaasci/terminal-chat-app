#ifndef UI_H
#define UI_H

#include <windows.h>
#include "../client/config.h"

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 256

#define MAX_USERS 20


void initUI();

void addMessage(const char* username, const char* message);

void setUsers(char users[][MAX_USERNAME], int count);

void drawUI();

void inputMessage(char* buffer, int size);

#endif