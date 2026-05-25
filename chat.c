#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "chat.h"

void joinChat(User currentUser) {
    Message newMessage;

    bool exitChat = false;

    strcpy(newMessage.sender, currentUser.userName);

    getchar();

    char ch;
    int i = 0;

    newMessage.text[0] = '\0';

    while (!exitChat)
    {
        system("cls");

        printf("==== Public Chat ====\n\n");

        showChat();

        printf("\n[/exit to quit]\n");
        printf("%s : %s", currentUser.userName, newMessage.text);

        if (_kbhit())
        {
            ch = _getch();

            // ENTER
            if (ch == '\r')
            {
                // exit command
                if (strcmp(newMessage.text, "/exit") == 0)
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

                time_t currentTime;
                time(&currentTime);

                struct tm *local = localtime(&currentTime);

                strftime(newMessage.time,
                         sizeof(newMessage.time),
                         "%H:%M",
                         local);

                fprintf(file,
                        "[%s] %s : %s\n",
                        newMessage.time,
                        newMessage.sender,
                        newMessage.text);

                fclose(file);

                // clear message
                i = 0;
                newMessage.text[0] = '\0';
            }

            // BACKSPACE
            else if (ch == '\b' && i > 0)
            {
                i--;
                newMessage.text[i] = '\0';
            }

            // NORMAL CHARACTER
            else if (i < MAX_TEXT - 1)
            {
                newMessage.text[i++] = ch;
                newMessage.text[i] = '\0';
            }
        }

        Sleep(100);
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