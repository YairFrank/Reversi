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
        //enable server to be stopped by user
        cout << "Enter exit to stop server" << endl;
        string str;
        cin >> str;
        if (str == "exit")
            server.stop();

    } catch (const char*msg) {
        cout << "Cannot start server. Reason: "<< msg<< endl;
        exit(-1);
    }
}