#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chat.h"

void joinChat(User currentUser) {
    Message newMessage;
    bool exitChat = false;
    strcpy(newMessage.sender, currentUser.userName);
    getchar();
    

    while (!exitChat)
    {
        system("cls");
        printf("==== Public Chat ====\n\n");
        showChat();

        printf("\n : ");
        fgets(newMessage.text, sizeof(newMessage.text), stdin);

        if (strcmp(newMessage.text, "/exit\n") == 0)
        {
            exitChat = true;
            continue;
        }
        

        FILE *file = fopen("chat.txt", "a");

        if (file == NULL)
        {
            printf("File could not be opened!");
            return;
        }

        fprintf(file, "%s : %s", newMessage.sender, newMessage.text);

        fclose(file);


        
    }
    

}

void showChat() {
    FILE *file = fopen("chat.txt", "r");
    char line[MAX_LINE_CHAT];

    if (file == NULL)
        {
            printf("File could not be opened!");
            return;
        }
    
        while (fgets(line, sizeof(line), file))
        {
            printf("%s", line);
        }
        fclose(file);
        

}