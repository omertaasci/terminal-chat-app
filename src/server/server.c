#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

#include "../client/chat.h"
#include "../client/config.h"

SOCKET clients[MAX_CLIENTS];
int clientCount = 0;

void broadcastMessage(ChatMessage *msg, SOCKET sender) {
    for (int i = 0; i < clientCount; i++)
    {
        send(clients[i], (char*)msg, sizeof(*msg), 0);
    }
    
}

void removeClient(SOCKET client) {
    for (int i = 0; i < clientCount; i++)
    {
        if (clients[i] == client)
        {
            clients[i] = clients[clientCount - 1];
            clientCount--;
            break;
        }
        
    }
    
}

// Client Handler
DWORD WINAPI handleClient(LPVOID lpParam) {
    SOCKET client = (SOCKET)lpParam;

    ChatMessage msg;
    int len;

    while (1)
    {
        len = recv(client, (char*)&msg, sizeof(msg), 0);
        // receive data from client into buffer
        // -1 leaves space for '\0'
        // 0 = no special flags meaning just get the data normally

        if (len <= 0)
        {
            printf("\nClient disconnected!");
            removeClient(client);
            break;
        }

        printf("%s: %s\n", msg.username, msg.message);
        broadcastMessage(&msg, client);
        
    }
    closesocket(client);
    return 0;
    
}

int main(void) {
    WSADATA wsa; // WSAStartup() stores Winsock information in this struct.
    SOCKET server, client; // socket handles for the server and connected client
    struct sockaddr_in addr; // stores an IPv4 address and port number
    ChatMessage msg;
    int len; // stores the number of bytes received

    WSAStartup(MAKEWORD(2, 2), &wsa); // Initialize the windows socket library before using sockets

    server = socket(AF_INET, SOCK_STREAM, 0); // creates an ipv4 tcp socket

    addr.sin_family = AF_INET; // use ipv4
    addr.sin_addr.s_addr = INADDR_ANY; // listen on all network interfaces(localhost, lan, internet if reachable)
    addr.sin_port = htons(5000); // use port 5000 (converted to network byte order)

    bind(server, (struct sockaddr*)&addr, sizeof(addr)); // bind server socket to ip and port in addr
    listen(server, 5);  // server starts listening for incoming connections, allowing up to 5 pending connection

    printf("Waiting for connection...");

    while (1)
    {
        client = accept(server, NULL, NULL);
        // accepts incoming connection from client.
        // NULL(1) = ignore client IP address. NULL(2) = ignore address length.

        if (clientCount >= MAX_CLIENTS)
        {
            printf("\nServer is full!");
            closesocket(client);

            continue;
        }

        clients[clientCount++] = client;
        printf("\nClient connected!\n");

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