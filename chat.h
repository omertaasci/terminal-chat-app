#ifndef CHAT_H
#define CHAT_H

#include "config.h"
#include "user.h"

void joinChat(User currentUser);
void showChat();

typedef struct 
{
    char sender[MAX_USERNAME];
    char text[MAX_TEXT];
} Message;



#endif