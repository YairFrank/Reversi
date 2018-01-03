

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include<vector>
#include <sstream>
#include "CommandsManager.h"



using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define MAX_COMMAND_LEN 50


Server::Server(int port): port(port), serverSocket(0), clientConnectingThread(0) {
    cout << "Server" << endl;


}

void Server::start() {
    //create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw runtime_error("Error on binding");
    }
    //start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    int rc = pthread_create(&clientConnectingThread, NULL, &getClients, (void*)serverSocket);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }

}


void* Server::getClients(void* serverSocket) {
    long serverSocketId = (long)serverSocket;
    pthread_t thread;
    vector<pthread_t> threads;
    int i = 1;

    //define the client socket's structures
    struct sockaddr_in playerAddress;
    socklen_t playerAddressLen;

    while (true) {
        //accept a players connection
        int playerSocket = accept(serverSocketId, (struct sockaddr *) &playerAddress, &playerAddressLen);
        if (playerSocket == -1) {
            throw "Error on accept";
        }
        threads.push_back(thread);
        int rc = pthread_create(&threads[i], NULL, &handleClient, (void *) playerSocket);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
    }
}


void* Server::handleClient(void* clientSocket) {

    int n;
    long sid = (long) clientSocket;
    char commandStr [MAX_COMMAND_LEN];
    istringstream iss;
    vector<string> args;
    vector<string>::iterator it;
    string s;

    //get clients command
    n = read(sid, &commandStr, sizeof(commandStr));
    if (n == -1) {
        cout << "error reading command" << endl;
        return NULL;
    }
    // Split the command string to the command name and the arguments
    string str(commandStr);
    iss.str(str);
    string command;
    iss >> command;
    while (iss) {
        string arg;
        iss >> arg;
        args.push_back(arg);
    }
    CommandsManager::getInstance()->executeCommand(command, args, sid);
    args.clear();
    return NULL;
}

void Server::stop() {
    vector<int> sockets;
    vector<int>::iterator itn;
    int clientsocket;

    pthread_cancel(clientConnectingThread);
    cout << "Server stopped" << endl;
    //close all clients sockets:

    GamesList* gl = GamesList::getGamesList();
    gl->getAllSockets(sockets);
    for (itn = sockets.begin(); itn != sockets.end(); ++itn) {
        clientsocket = *itn;
        close(clientsocket);
    }
    close(serverSocket);
}


