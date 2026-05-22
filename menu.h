#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "user.h"

int showMenu(User currentUser);
void handleChoice(int choice, User currentUser, bool *logged, bool *running);

#endif