#include<iostream>
#include<stdlib.h>
#include <fstream>
#include "Server.h"
using namespace std;
int main() {
    int port;
    ifstream inFile;
    inFile.open("infoserver.txt");
    inFile >> port;
    inFile.close();
    Server server(port);
    try
    {
        server.start();
    } catch (const char*msg) {
        cout << "Cannot start server. Reason: "<< msg<< endl;
        exit(-1);
    }
}