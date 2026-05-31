#include <stdio.h>
#include <winsock2.h>
#include <conio.h>
#include <string.h>

#include "chat.h"
#include "user.h"

void publicChat(User *currentUser) {
    WSADATA wsa; // WSAStartup() stores Winsock information in this struct.
    SOCKET sock; // socket handle
    struct sockaddr_in server; // stores an IPv4 address and port number

    ChatMessage msg;


    WSAStartup(MAKEWORD(2,2), &wsa);; // Initialize the windows socket library before using sockets

    sock = socket(AF_INET, SOCK_STREAM, 0); // creates an ipv4 tcp socket

    server.sin_family = AF_INET; // use ipv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5000); // use port 5000 (converted to network byte order)

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Server is offline!\n");
        closesocket(sock);
        WSACleanup();
        _getch();
        return;
    }

    printf("Conntected to server!");
    printf("\nWelcome %s\n", currentUser->userName);

    printf("\nMessage : ");
    fgets(msg.message, sizeof(msg.message), stdin); // message input from keyboard
    msg.message[strcspn(msg.message, "\n")] = '\0';

    strcpy(msg.username, currentUser->userName);
    
    if (send(sock, (char*)&msg, sizeof(msg), 0) == SOCKET_ERROR)
    {
        printf("Failed to send message!\n");
    }

    //send(sock, (char*)&msg, sizeof(msg), 0);

    closesocket(sock);
    WSACleanup();
    _getch();
    
}