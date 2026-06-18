# Terminal Chat App

A Windows terminal-based client-server chat application written in C.

This project was built as a learning project to practice socket programming, multi-client communication, user authentication, role-based access control and modular C project structure.

## Features

* Client-server architecture
* Multiple client connections
* User login system
* Role-based access control
* Admin user management
* Add, edit, delete and search users
* Online users list
* Chat message broadcasting
* Failed login attempt limit
* File-based user storage
* Server-side logging
* Modular C source structure

## Technologies Used

* C
* Winsock
* Windows API
* Multithreading
* File I/O
* Terminal UI

## Project Structure

```txt
terminal-chat-app/
├── src/
│   ├── client/
│   │   ├── main.c
│   │   ├── auth.c
│   │   ├── chat.c
│   │   ├── menu.c
│   │   ├── ui.c
│   │   └── user.c
│   └── server/
│       └── server.c
├── data/
│   ├── users.txt
│   └── log.txt
├── README.md
└── build.bat
```

## How It Works

The application is split into two main parts:

* The server listens for incoming client connections and handles message broadcasting.
* The client allows users to log in, use the chat system and access role-based menu options.

Users are stored in a text file for learning purposes. Admin users can manage other users through the terminal interface.

## Build

This project is designed for Windows because it uses Winsock.

You can build the project with GCC:

```bash
build.bat
```

Example `build.bat`:

```bat
@echo off

if not exist bin mkdir bin

gcc src/client/main.c src/client/auth.c src/client/chat.c src/client/menu.c src/client/ui.c src/client/user.c -o bin/client.exe -lws2_32

gcc src/server/server.c -o bin/server.exe -lws2_32

echo Build completed.
```

## Run

Open two terminals.

Terminal 1:

```bash
bin\server.exe
```

Terminal 2:

```bash
bin\client.exe
```

To test multiple users, open more client terminals and run:

```bash
bin\client.exe
```

## Example Usage

1. Start the server.
2. Start one or more clients.
3. Log in with an existing user account.
4. Send messages through the terminal chat.
5. Use admin options if the logged-in user has admin permissions.

## Learning Goals

The main goal of this project was to understand how a basic client-server application works in C.

Main topics practiced:

* Creating a TCP server with Winsock
* Connecting multiple clients
* Sending and receiving messages
* Separating client and server logic
* Managing users with file-based storage
* Using roles and permissions
* Organizing a C project into multiple source files
* Debugging network and terminal applications

## Known Limitations

This project is not production-ready. It was created for learning purposes.

Current limitations:

* Windows-only because it uses Winsock
* No message encryption
* Passwords are stored in plain text
* File-based storage instead of a database
* Basic terminal user interface
* No direct message system yet

## Future Improvements

Possible improvements:

* Add password hashing
* Add direct private messages
* Improve terminal UI
* Add SQLite database support
* Add better server error handling
* Add command-based chat features
* Add cross-platform socket support

## Screenshots

Screenshots can be added here later.

```md
![Login screen](<img width="1096" height="578" alt="login" src="https://github.com/user-attachments/assets/088dcc7b-5a8f-472b-92c2-a0dfac4e8bfe" />)
![Chat screen](<img width="1097" height="575" alt="chat" src="https://github.com/user-attachments/assets/2de2f34b-6f52-43ef-87b7-67fb28fadc29" />)
![Admin menu](<img width="1100" height="579" alt="admin" src="https://github.com/user-attachments/assets/a7494e9a-fc55-4132-a521-3cdf6b0d6b3c" />)
```

## Project Status

The core version of the project is complete. The application supports user login, role-based actions, admin user management, multi-client chat and server logging.

Further improvements may be added as part of continued learning.

## Author

Created by [omertaasci](https://github.com/omertaasci)
