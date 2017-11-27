//
// Created by yair on 27/11/17.
//

#include "Menu.h"
#include "ReversieGame.h"
#include <iostream>

using namespace std;

Menu::Menu(){}

void Menu::play() {
    int a;
    cout<<"Hello."<<endl<<"For human vs human press 1."<<endl<<"For human vs AI press 2."<<endl;
    cin>>a;
    while(a!=1&&a!=2){
        cout<<"Wrong number."<<endl
            <<"For human vs human press 1."<<endl<<"For human vs AI press 2."<<endl;
        cin>>a;
    }
    ReversieGame g (a);
    g.play();
}