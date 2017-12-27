// leah orlin 313357725
// yair frank 203699566

#include "Menu.h"
#include "ReversieGame.h"
#include "RemoteGame.h"

using namespace std;

Menu::Menu(){}

void Menu::play() {
    int a;
    cout<<"Hello."<<endl<<"Choose an opponent type:"<<endl<<"1. a human local player"<<endl
            <<"2. an AI player"<<endl<<"3. a remote player"<<endl;
    cin>>a;
    while(cin.fail() || (a!=1 && a!=2 && a!=3)){
        cout<<"Wrong number."<<endl
            <<"For human vs human press 1."<<endl<<"For human vs AI press 2."
            <<endl<<"3. a remote player"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin>>a;
    }
    if (a==1||a==2){
        ReversieGame g (a);
        g.play();
    }
    else{
        RemoteGame g;
        g.play();
    }
}