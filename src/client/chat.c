#include <stdio.h>
#include <winsock2.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#include "chat.h"
#include "user.h"
#include "ui.h"


DWORD WINAPI receiveMessages(LPVOID lpParam) { // Thread function that constantly receives messages from server
    SOCKET sock = (SOCKET)lpParam; // Convert thread parameter into socket variable

    ChatMessage msg; // Stores received message data
    int len; // Stores how many bytes were received

    while (1) // Keep listening for messages forever
    {
        len = recv(sock, (char*)&msg, sizeof(msg), 0); // Receive message data from server socket

        if (len <= 0) // If recv returns 0 or less or client disconnected or an error happened
        {
            printf("\nDisconnected from server!");
            break;
        }

        if (msg.type == 1)
        {
            char users[MAX_USERS][MAX_USERNAME];

            int count = 0;

            char* token = strtok(msg.message, ",");

            while (token != NULL)
            {
                strcpy(users[count], token);

                count++;

                token = strtok(NULL, ",");
            }

            setUsers(users, count);
        }
        else
        {
            addMessage(msg.username, msg.message); // Add received message to chat
        }
        
    }
    
    return 0;
    
}

void publicChat(User *currentUser) {
    WSADATA wsa; // Stores Winsock startup information
    SOCKET sock; // socket handle
    struct sockaddr_in server; // Stores server IP address and port information

    ChatMessage msg;


    WSAStartup(MAKEWORD(2,2), &wsa);; // Start Winsock library before using sockets
    // MAKEWORD(2,2) means use winsock version 2.2

    sock = socket(AF_INET, SOCK_STREAM, 0); // creates an ipv4 tcp socket

    server.sin_family = AF_INET; // use ipv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost
    server.sin_port = htons(5000); // use port 5000 (converted to network byte order)

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) // Try connecting to the chat server
    {
        printf("Server is offline!\n");
        closesocket(sock);
        WSACleanup();
        _getch();
        return;
    }

    strcpy(msg.username, currentUser->userName); // msg.username = currentuser.username
    msg.type = 0;
    msg.message[0] = '\0'; // empty message
    send(sock, (char*)&msg, sizeof(msg), 0); // sends it just to get the username when user connects to server

    // Create separate thread for receiving messages
    // So receiving and sending can happen at the same time
    CreateThread(
        NULL,
        0,
        receiveMessages,
        (LPVOID)sock,
        0,
        NULL
    );

    initUI();

    addMessage("SYSTEM", "Connected to server");

    

    while (1) // Keep chat running forever
    {
        inputMessage(msg.message, sizeof(msg.message)); // Get message input from user

        strcpy(msg.username, currentUser->userName); // Copy current username into message struct
        msg.type = 0;
        if (strcmp(msg.message, "/exit") == 0) // If user types /exit
        {
            printf("Disconnected! \nPress any key.");
            break;
        }


        if (send(sock, (char*)&msg, sizeof(msg), 0) == SOCKET_ERROR) // Try to send message to server
        {
            // if failed show error message in chat
            addMessage("SYSTEM", "Failed to send message");
            break;
        }

        addMessage(currentUser->userName, msg.message); // Add own message to local chat window
    }
    

    //send(sock, (char*)&msg, sizeof(msg), 0);

    closesocket(sock);
    WSACleanup();
    _getch();
    
}