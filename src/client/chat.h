#ifndef CHAT_H
#define CHAT_H

#include "user.h"
#include "config.h"

typedef struct {
    char username[MAX_USERNAME];
    char message[MAX_MESSAGE];
} ChatMessage;

void publicChat(User *currentUser);

#endif