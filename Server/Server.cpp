

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
typedef struct threadInfo {long serverSock; vector<pthread_t>* pthreads;} threadInfo;

Server::Server(int port): port(port), serverSocket(0), clientConnectingThread(0) {
    cout << "Server" << endl;


}

void Server::start() {
    //create socket
    long serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    threadInfo* ti = new threadInfo;

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
    ti->serverSock = serverSocket;
    ti->pthreads = &threads;
    int rc = pthread_create(&clientConnectingThread, NULL, &getClients, (void*)ti);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }

}


void* Server::getClients(void* tinfo) {

    threadInfo* ti = (threadInfo*) tinfo;
    long serverSid = ti->serverSock;

    int i = 0;

    //define the client socket's structures
    struct sockaddr_in playerAddress;
    socklen_t playerAddressLen;

    while (true) {
        //accept a players connection
        int playerSocket = accept(serverSid, (struct sockaddr *) &playerAddress, &playerAddressLen);

        if (playerSocket == -1) {
            throw "Error on accept";
        }
        pthread_t thread;
        ti->pthreads->push_back(thread);

        int rc = pthread_create(&thread, NULL, &handleClient, (void *) playerSocket);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        i++;
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

    vector<pthread_t>::iterator it;
    pthread_t pt;
    vector<int> sockets;
    vector<int>::iterator itn;
    int clientsocket;
    int i = 0;

    GamesList* gl = GamesList::getGamesList();
    gl->getAllSockets(sockets);
    for (itn = sockets.begin(); itn != sockets.end(); ++itn) {
        clientsocket = *itn;
        close(clientsocket);
    }

    //close all client-handling threads
    for (it = threads.begin(); it != threads.end(); ++it) {
        //cout<<"canceling threads"<<endl;
        pthread_cancel(*it);
    }


    //close all clients sockets:


    pthread_cancel(clientConnectingThread);

    close(serverSocket);
    cout << "Server stopped" << endl;
}


