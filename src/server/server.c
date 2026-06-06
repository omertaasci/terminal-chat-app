#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

#include "../client/chat.h"
#include "../client/config.h"

SOCKET clients[MAX_CLIENTS];
int clientCount = 0;
char onlineUsers[MAX_CLIENTS][MAX_USERNAME];

void sendUserList() {
    ChatMessage msg;

    strcpy(msg.username, "SERVER");

    msg.type = 1; // user list type

    msg.message[0] = '\0';

    for (int i = 0; i < clientCount; i++)
    {
        strcat(msg.message, onlineUsers[i]);

        if (i < clientCount - 1)
        {
            strcat(msg.message, ",");
        }       
    }

    for (int i = 0; i < clientCount; i++)
    {
        send(clients[i], (char*)&msg, sizeof(msg), 0);
    }
    
    
}

void broadcastMessage(ChatMessage *msg, SOCKET sender) // send the msg to all of the users except sender
{
    for (int i = 0; i < clientCount; i++) 
    {
        if (clients[i] == sender) // sender doesnt receive his own msg
        {
            continue;
        }

        if (send(clients[i], (char*)msg, sizeof(*msg), 0) == SOCKET_ERROR) // try to send the message, if sending fails print error
        {
            printf("Failed to send message to client %d\n", i);
        }
    }
}

void removeClient(SOCKET client) { // remove disconnected client from the list
    for (int i = 0; i < clientCount; i++)
    {
        if (clients[i] == client)
        {
            clients[i] = clients[clientCount - 1];
            strcpy(onlineUsers[i], onlineUsers[clientCount - 1]);
            clientCount--;
            sendUserList();
            break;
        }
        
    }
    
}

// Client Handler
DWORD WINAPI handleClient(LPVOID lpParam) { // Handles one client connection in a separate thread
    SOCKET client = (SOCKET)lpParam; // Get the client socket from thread parameter

    ChatMessage msg; // Stores incoming message data
    ChatMessage sysMsg;
    int len; // Stores how many bytes were received

    // first message = username
    len = recv(client, (char*)&msg, sizeof(msg), 0);
    msg.type = 0;

    if (len <= 0)
    {
        closesocket(client);
        return 0;
    }
    printf("%s connected.\n", msg.username);

    // user connected broadcast for all users
    sysMsg.type = 0;
    strcpy(sysMsg.username, "SYSTEM");
    sprintf(sysMsg.message, "%s connected.\n", msg.username);
    broadcastMessage(&sysMsg, INVALID_SOCKET);

    char currentUsername[MAX_USERNAME];
    strcpy(currentUsername, msg.username);

    for (int i = 0; i < clientCount; i++) // adding user to onlineUsers
    {
        if (clients[i] == client)
        {
            strcpy(onlineUsers[i], msg.username);
            break;
        }
        
    }

    sendUserList();
    

    while (1) // Keep listening to client messages forever
    {
        len = recv(client, (char*)&msg, sizeof(msg), 0);
        // receive message data from client socket
        // -1 leaves space for '\0'
        // 0 = no special flags meaning just get the data normally

        if (len <= 0) // If recv returns 0 or less or client disconnected or an error happened
        {
            printf("\n%s disconnected.", currentUsername);
            removeClient(client); // Remove client from clients array

            // user disconnected broadcast for all users
            sysMsg.type = 0;
            strcpy(sysMsg.username, "SYSTEM");
            sprintf(sysMsg.message, "%s disconnected.\n", msg.username);
            broadcastMessage(&sysMsg, INVALID_SOCKET);

            break;
        }

        printf("%s: %s\n", msg.username, msg.message);
        broadcastMessage(&msg, client); // Send message to all other connected clients
    }
    closesocket(client);
    return 0;
    
}

int main(void) {
    WSADATA wsa; // WSAStartup() stores Winsock startup information
    SOCKET server, client; // socket handles for the server and connected client
    struct sockaddr_in addr; // Stores server IP address and port information
    ChatMessage msg; // Message buffer struct
    int len; // stores the number of bytes received

    WSAStartup(MAKEWORD(2, 2), &wsa); // Start Winsock library before using sockets

    server = socket(AF_INET, SOCK_STREAM, 0); // Create TCP IPv4 server socket

    addr.sin_family = AF_INET; // use ipv4
    addr.sin_addr.s_addr = INADDR_ANY; // listen on all network interfaces(localhost, lan, internet if reachable)
    addr.sin_port = htons(5000); // use port 5000 (converted to network byte order)
    // htons converts port number to network byte order

    bind(server, (struct sockaddr*)&addr, sizeof(addr)); // Attach socket to IP address and port
    listen(server, 5);  // server starts listening for incoming connections, allowing up to 5 pending connection

    printf("Waiting for connection...\n");

    while (1) // Keep server running forever
    {
        client = accept(server, NULL, NULL);
        // accepts incoming connection from client.
        // NULL(1) = ignore client IP address. NULL(2) = ignore address length.

        if (clientCount >= MAX_CLIENTS) // If server reached max client limit
        {
            printf("\nServer is full!");
            closesocket(client); // Reject client connection

            continue;
        }

        clients[clientCount++] = client; // Add client socket to clients array
        //printf("\nClient connected!\n");

        // Creates separate thread for this client
        // So multiple clients can work at the same time
        CreateThread( 
            NULL,
            0,
            handleClient,
            (LPVOID)client,
            0,
            NULL
        );
    }
    
    closesocket(client);
    closesocket(server);
    WSACleanup();

    _getch();
    return 0;
}