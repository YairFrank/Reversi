#include<iostream>
#include<stdlib.h>
#include "Server.h"
using namespace std;
int main() {
    Server server(8234);
    try
    {
        server.start();
    } catch (const char*msg) {
        cout << "Cannot start server. Reason: "<< msg<< endl;
        exit(-1);
    }
}
