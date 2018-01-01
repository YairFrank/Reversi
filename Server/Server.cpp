//
// Created by leah on 28/12/17.
//

//
// Created by yair on 09/12/17.
//

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
    //pthread_t quitStatusThread, clientConnectingThread;


    /*int rc = pthread_create(&quitStatusThread, NULL, quitStatus, (void*)this);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }*/

    int rc = pthread_create(&clientConnectingThread, NULL, &getClients, (void*)serverSocket);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }

}


void* Server::getClients(void* serverSocket) {
    long serverSocketId = (long)serverSocket;
    vector<pthread_t> threads;
    vector<pthread_t>::iterator it;
    vector<int>::iterator itn;
    int clientsocket;
    pthread_t thread;
    int i = 1;
    vector<int> sockets;

    //create socket
    //ths->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    //if (ths->serverSocket == -1) {
    //    throw "Error opening socket";
    //}



    //define the client socket's structures
    struct sockaddr_in playerAddress;
    socklen_t playerAddressLen;

    while (true) {
        cout << "Waiting for client connections..." << endl;
        //accept a players connection
        int playerSocket = accept(serverSocketId, (struct sockaddr *) &playerAddress, &playerAddressLen);
        cout << "Client number " << i << " connected" << endl;
        if (playerSocket == -1) {
            throw "Error on accept";
        }
        threads.push_back(thread);
        cout << "In getClients: creating thread " << i << endl;
        int rc = pthread_create(&threads[i], NULL, &handleClient, (void *) playerSocket);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        i++;
    }

    //server needs to close all threads connected to clients and exit.
    for (it = threads.begin(); it != threads.end(); ++it) {
        thread = *it;
        pthread_cancel(thread);
    }
    //close all clients sockets:

    GamesList* gl = GamesList::getGamesList();
    gl->getAllSockets(sockets);
    for (itn = sockets.begin(); itn != sockets.end(); ++itn) {
        clientsocket = *itn;
        close(clientsocket);
    }
    pthread_exit(NULL);
}


void* Server::handleClient(void* clientSocket) {

    int n;
    //clientData cd;
    long sid = (long) clientSocket;
    char commandStr [MAX_COMMAND_LEN];
    istringstream iss;
    vector<string> args;
    vector<string>::iterator it;
    string s;
    //CommandsManager cm;
    //create a command manager
    //cm = new CommandsManager();

    //get clients command
    n = read(sid, &commandStr, sizeof(commandStr));
    if (n == -1) {
        cout << "error reading command" << endl;
        return NULL;
    }
    cout << "Received command: " << commandStr << endl;
    // Split the command string to the command name and the arguments
    string str(commandStr);
    iss.str(str);
    string command;
    iss >> command;
    while (iss) {

        string arg;
        iss >> arg;
        args.push_back(arg);
        cout << "added arg "<< arg <<endl;
    }
    for (it = args.begin(); it != args.end(); ++it) {
        s = *it;

    }
    CommandsManager::getInstance()->executeCommand(command, args, sid);
    args.clear();
    return NULL;
}

void Server::stop() {
    pthread_cancel(clientConnectingThread);
    close(serverSocket);
    cout << "Server stopped" << endl;
}


void* Server::quitStatus(void* class_ptr) {
    Server* ths = (Server*)class_ptr;
    string q;
    while(true) {

        cin >> q;
        if (q == "exit") {
            ths->quit = true;
            break;
        }
    }
    pthread_exit(NULL);
}
void Server::assignSymbol(int clientSocket, int numPlayer) {
    int n = write(clientSocket, &numPlayer, sizeof(numPlayer));
    if (n == -1) {
        cout << "error writing to socket"<< endl;
        return;
    }
}

bool Server::isWin(coordinate m) {
    if ((m.x == -3) && (m.y == -3)) {
        return true;
    }
    return false;
}

//void Server::stop() {
//    close(serverSocket);
//}

bool Server::isQuit() const {
    return quit;
}

void Server::setQuit(bool quit) {
    Server::quit = quit;
}
int Server::getServerSocket() const {
    return serverSocket;
}

void Server::setServerSocket(int serverSocket) {
    Server::serverSocket = serverSocket;
}

int Server::getPort() const {
    return port;
}

void Server::setPort(int port) {
    Server::port = port;
}
