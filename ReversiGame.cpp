//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#include "ReversiGame.h"
#include "ReversiGameLogic.h"
#include <algorithm>
#include <limits>
using namespace std;

ReversiGame::ReversiGame (){}

int ReversiGame::getNumberFromUser() {
    int num;
    while (true) {
        cin >> num;
        if (!cin.fail()) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            return num;
        }
        cout << "Please enter numbers only." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    }
}


Player & ReversiGame::getRival(Player &p, Player &p1, Player &p2){
    if (p.getName()=='X')
        return p2;
    else
        return p1;
}

void ReversiGame::game(){
    const int size=8;
    Board b(size);
    vector <Disc> list;
    Player p1('X',2);
    Player p2('O',2);
    Player *p=&p1;
    b.print();
    cout<<endl;
    int count=0, flag=0;
    vector<Disc> choise;
    ReversiGameLogic logic (b.getBoard(), size, choise);
    logic.updateList(p->getName(), getRival(*p,p1,p2).getName(), list);
    while (true){
        while(!list.empty()) {
            if (!logic.getChoise().empty())
                cout<<getRival(*p,p1,p2).getName()<< " played ("<< logic.getChoise()[0].getDiscRow()+1<<","<<logic.getChoise()[0].getDiscColumn()+1<<")"<<endl<<endl;
            count=0;
            cout<<p->getName() <<": It's your move."<<endl<<"Your possible moves: ";
            for (int d=0; d<list.size();d++) {
                cout<<" ("<< list[d].getDiscRow()+1<<","<< list[d].getDiscColumn()+1<<") ";
            }
            cout<<endl<<endl;
            cout<<"Please enter your move (row and press enter, column and press enter again): "<<endl;
            int  i=getNumberFromUser(), j=getNumberFromUser();
            for (int d=0; d<list.size();d++){
                if(list[d].getDiscRow()==i-1&&list[d].getDiscColumn()==j-1){
                    flag=1;
                    break;
                }
            }
            while (!flag) {
                cout << "Illegal move. Please enter your move (row and press enter, column and press enter again): ";
                int  e=getNumberFromUser(), f=getNumberFromUser();
                i=e;
                j=f;
                for (int d=0; d<list.size();d++) {
                    if (list[d].getDiscRow() == i-1 && list[d].getDiscColumn() == j-1) {
                        flag = 1;
                        break;
                    }
                }
            }
            flag=0;
            int v = i-1;
            int w = j-1;
            logic.addAndChange(*p, getRival(*p,p1,p2), v, w, b);
            b.print();
            cout<<endl;
            p=logic.switchPlayer(p, p1, p2);
            list.clear();
            logic.updateList(p->getName(), getRival(*p,p1,p2).getName(), list);
        }
        if (count==1){
            cout<<"No possible moves. Play passes back to the other player."<<endl;
            if (p1.getCount()>p2.getCount())
                cout<<"The winner is: X"<<endl;
            if (p1.getCount()<p2.getCount())
                cout<<"The winner is: O"<<endl;
            if(p1.getCount()==p2.getCount())
                cout<<"It's a tie."<<endl;
            break;
        }
        count++;
        p=logic.switchPlayer(p, p1, p2);
        list.clear();
        logic.updateList(p->getName(), getRival(*p,p1,p2).getName(), list);
        cout<<"No possible moves. Play passes back to the other player."<<endl;
    }
}