#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

#include "../client/chat.h"

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
    listen(server, 1);  // server starts listening for incoming connections, allowing up to 1 pending connection

    printf("Waiting for connection...");

    client = accept(server, NULL, NULL); // accepts incoming connection from client NULL(1) = ignore client IP address. NULL(2) = ignore address length.

    printf("\nClient connected!");

    len = recv(client, (char*)&msg, sizeof(msg), 0);
    // receive data from client into buffer
    // -1 leaves space for '\0'
    // 0 = no special flags meaning just get the data normally

    if (len > 0)
    {
        printf("\n\n%s: %s\n", msg.username, msg.message);
    }
    
    closesocket(client);
    closesocket(server);
    WSACleanup();

    _getch();
    return 0;
}