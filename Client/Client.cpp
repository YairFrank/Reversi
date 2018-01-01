//
// Created by yair on 05/12/17.
//

#include "Client.h"
#include "Shortcuts.h"
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

class PlayMessage;

using namespace std;

Client::Client() = default;

Client::Client(const char *serverIP, int serverPort):
        serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
}

void Client::connectToServer() {
// Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
// Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
    if(server == NULL) {
        throw "Host is unreachable";
    }
// Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char*)&address,sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
//htonsconverts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
// Establish a connection with the TCP server
    if(connect(clientSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout<<"Connected to server"<<endl;
}

void Client::sendMessage(Shortcuts::PlayMessage& play) {
// Write the coordinates to the socket
    int n = write(clientSocket, &play, 100);
    if (n == -1) {
        throw "Server is closed, dude";
    }
}
void Client::getMessage(Shortcuts::PlayMessage& play) {
// Read the coordinates from the server
    int n = read(clientSocket, &play, 100);
    if (n == -1) {
        throw "Server is closed, dude";
    }
}

int Client::getSocket() {
    return clientSocket;
}