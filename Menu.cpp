// leah orlin 313357725
// yair frank 203699566

#include "Menu.h"
#include "ReversieGame.h"

using namespace std;

Menu::Menu(){}

void Menu::play() {
    int a;
    cout<<"Hello."<<endl<<"For human vs human press 1."<<endl<<"For human vs AI press 2."<<endl;
    cin>>a;
    while(cin.fail() || (a!=1 && a!=2)){
        cout<<"Wrong number."<<endl
            <<"For human vs human press 1."<<endl<<"For human vs AI press 2."<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin>>a;
    }
    ReversieGame g (a);
    g.play();
}
