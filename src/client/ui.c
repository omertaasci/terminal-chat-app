#include "../client/ui.h"
#include "../client/config.h"

#include <stdio.h>
#include <string.h>

#define CHAT_X 1
#define CHAT_Y 1
#define CHAT_WIDTH 70
#define CHAT_HEIGHT 20

#define USER_X 73
#define USER_Y 1
#define USER_WIDTH 25
#define USER_HEIGHT 20

#define INPUT_Y 23

typedef struct
{
    char text[MAX_MESSAGE_LEN];
} UIMessage;

static UIMessage messages[MAX_MESSAGES];
static int messageCount = 0;

static char onlineUsers[MAX_USERS][MAX_USERNAME];
static int onlineUserCount = 0;

static HANDLE hConsole;
static HANDLE hMutex;

void gotoXY(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(hConsole, c);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 1;
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(hConsole, &cursor);
}

void drawBox(int x, int y, int width, int height)
{
    int i;

    gotoXY(x, y);
    printf("+");

    for(i = 0; i < width - 2; i++)
        printf("-");

    printf("+");

    for(i = 1; i < height - 1; i++)
    {
        gotoXY(x, y + i);
        printf("|");

        gotoXY(x + width - 1, y + i);
        printf("|");
    }

    gotoXY(x, y + height - 1);
    printf("+");

    for(i = 0; i < width - 2; i++)
        printf("-");

    printf("+");
}

void initUI()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    hMutex = CreateMutex(NULL, FALSE, NULL);

    hideCursor();

    drawUI();
}

void drawMessages()
{
    int start = 0;

    if(messageCount > CHAT_HEIGHT - 2)
        start = messageCount - (CHAT_HEIGHT - 2);

    int row = 0;

    for(int i = start; i < messageCount; i++)
    {
        gotoXY(CHAT_X + 1, CHAT_Y + 1 + row);

        printf("%-66s", messages[i].text);

        row++;
    }
}

void drawUsers()
{
    for(int y = 0; y < USER_HEIGHT - 2; y++)
    {
        gotoXY(USER_X + 1, USER_Y + 1 + y);

        printf("%-23s", "");
    }

    gotoXY(USER_X + 2, USER_Y + 1);

    printf("ONLINE USERS");

    for(int i = 0; i < onlineUserCount; i++)
    {
        gotoXY(USER_X + 2, USER_Y + 3 + i);

        printf("%-20s", onlineUsers[i]);
    }
}

void clearInside()
{
    for(int y = 1; y < CHAT_HEIGHT - 1; y++)
    {
        gotoXY(CHAT_X + 1, CHAT_Y + y);

        for(int x = 0; x < CHAT_WIDTH - 2; x++)
            printf(" ");
    }

    for(int y = 1; y < USER_HEIGHT - 1; y++)
    {
        gotoXY(USER_X + 1, USER_Y + y);

        for(int x = 0; x < USER_WIDTH - 2; x++)
            printf(" ");
    }
}

void drawUI()
{
    WaitForSingleObject(hMutex, INFINITE);

    system("cls");

    drawBox(CHAT_X, CHAT_Y, CHAT_WIDTH, CHAT_HEIGHT);

    drawBox(USER_X, USER_Y, USER_WIDTH, USER_HEIGHT);

    drawBox(1, INPUT_Y, 97, 3);

    drawMessages();

    drawUsers();

    gotoXY(3, INPUT_Y + 1);
    printf("Message: ");

    fflush(stdout);

    ReleaseMutex(hMutex);
}

void addMessage(const char* username, const char* message)
{
    WaitForSingleObject(hMutex, INFINITE);

    if(messageCount >= MAX_MESSAGES)
    {
        for(int i = 1; i < MAX_MESSAGES; i++)
        {
            strcpy(messages[i - 1].text, messages[i].text);
        }

        messageCount = MAX_MESSAGES - 1;
    }

    snprintf(
        messages[messageCount].text,
        MAX_MESSAGE_LEN,
        "%s: %s",
        username,
        message
    );

    messageCount++;

    ReleaseMutex(hMutex);

    drawUI();
}

void setUsers(char users[][MAX_USERNAME], int count)
{
    WaitForSingleObject(hMutex, INFINITE);

    onlineUserCount = count;

    for(int i = 0; i < count; i++)
    {
        strcpy(onlineUsers[i], users[i]);
    }

    ReleaseMutex(hMutex);

    drawUI();
}

void inputMessage(char* buffer, int size)
{
    gotoXY(12, INPUT_Y + 1);

    printf("%-80s", "");

    gotoXY(12, INPUT_Y + 1);

    fgets(buffer, size, stdin);

    buffer[strcspn(buffer, "\n")] = 0;
}