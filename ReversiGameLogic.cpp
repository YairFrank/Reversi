//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#include "ReversiGameLogic.h"


ReversiGameLogic::ReversiGameLogic(Disc** m, int size, vector<Disc>& choise): m (m), size (size), choise (choise){}
void ReversiGameLogic::updateList(char current, char other, vector <Disc> & list){
    for(int k=0;k<size;k++){
        for(int l=0;l<size;l++){
            if(m[k][l].getDisc()==' '){
                int i=k,j=l;
                if (i>=2) {
                    while (m[i-1][j].getDisc()==other&&i-2>=0){
                        if (m[i-1][j].getDisc()==other&&m[i-2][j].getDisc()==current){
                            options(k, l, list);
                            break;
                        }else{
                            i--;
                        }
                    }
                }
                i=k;
                if (i<=size-3){
                    while (m[i+1][j].getDisc()==other&&i+2<=size-1){
                        if (m[i+1][j].getDisc()==other&&m[i+2][j].getDisc()==current){
                            options(k, l, list);
                            break;
                        }else{
                            i++;
                        }
                    }
                }
                i=k;
                if (j>=2)
                {
                    while(m[i][j-1].getDisc()==other&&j-2>=0){
                        if (m[i][j-1].getDisc()==other&&m[i][j-2].getDisc()==current){
                            options(k, l, list);
                            break;
                        }else{
                            j--;
                        }
                    }
                }
                j=l;
                if (j<=size-3){
                    while(m[i][j+1].getDisc()==other&&j+2<=size-1) {
                        if (m[i][j+1].getDisc()==other&&m[i][j+2].getDisc()==current){
                            options(k, l, list);
                            break;
                        }else{
                            j++;
                        }
                    }
                }
                j=l;
                if(i>=2&&j>=2){
                    while (m[i-1][j-1].getDisc()==other&&i-2>=0&&j-2>=0) {
                        if (m[i - 1][j - 1].getDisc() == other && m[i - 2][j - 2].getDisc() == current){
                            options(k, l, list);
                            break;
                        }else{
                            i--;
                            j--;
                        }
                    }
                }
                i=k;
                j=l;
                if(i>=2&&j<=size-3){
                    while(m[i-1][j+1].getDisc()==other&&i-2>=0&&j+2<=size-1){
                        if (m[i-1][j+1].getDisc()==other&&m[i-2][j+2].getDisc()==current){
                            options(k, l, list);
                            break;
                        }else{
                            i--;
                            j++;
                        }
                    }
                }
                i=k;
                j=l;
                if (i<=size-3&&j>=2){
                    while (m[i+1][j-1].getDisc()==other&&i+2<=size-1&&j-2>=0){
                        if (m[i+1][j-1].getDisc()==other&&m[i+2][j-2].getDisc()==current){
                            options(k, l, list);
                            break;
                        }else{
                            i++;
                            j--;
                        }
                    }
                }
                i=k;
                j=l;
                if(i<=size-3&&j<=size-3) {
                    while (m[i + 1][j + 1].getDisc() == other&&i+2<=size-1&&j+2<=size-1) {
                        if (m[i + 1][j + 1].getDisc() == other && m[i + 2][j + 2].getDisc() == current){
                            options(k, l, list);
                            break;
                        }else{
                            i++;
                            j++;
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<list.size();i++){
        for(int j=0;j<list.size();j++){
            if(list[i].getDiscRow()==list[j].getDiscRow()&&list[i].getDiscColumn()==list[j].getDiscColumn()&&i!=j)
                list.erase(list.begin()+j);
        }
    }
}

void ReversiGameLogic::addAndChange (Player& p1, Player &p2, int& k, int& l, Board& b){
    int i=k, j=l, c=0, count=0;
    m[i][j].setDisc(p1.getName());
    b.putDisk(p1.getName(),i,j);
    count++;
    if (i>=2) {
        while (i-2>=0&&m[i-1][j].getDisc()==p2.getName()){
            if (m[i-1][j].getDisc()==p2.getName()&&m[i-2][j].getDisc()==p1.getName()){
                i=k;
                for (int n=0;n<=c;n++){
                    i--;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            i--;
            c++;
        }
    }
    c=0;
    i=k;
    if (i<=size-3){
        while (i+2<=size-1&&m[i+1][j].getDisc()==p2.getName()){
            if (m[i+1][j].getDisc()==p2.getName()&&m[i+2][j].getDisc()==p1.getName()){
                i=k;
                for (int n=0;n<=c;n++){
                    i++;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            i++;
            c++;
        }
    }
    c=0;
    i=k;
    if (j>=2) {
        while(j-2>=0&&m[i][j-1].getDisc()==p2.getName()){
            if (m[i][j-1].getDisc()==p2.getName()&&m[i][j-2].getDisc()==p1.getName()){
                j=l;
                for (int n=0;n<=c;n++){
                    j--;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            j--;
            c++;
        }
    }
    c=0;
    j=l;
    if (j<=size-3){
        while(j+2<=size-1&&m[i][j+1].getDisc()==p2.getName()) {
            if (m[i][j+1].getDisc()==p2.getName()&&m[i][j+2].getDisc()==p1.getName()){
                j=l;
                for (int n=0;n<=c;n++){
                    j++;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            j++;
            c++;
        }
    }
    c=0;
    j=l;
    if(i>=2&&j>=2){
        while (i-2>=0&&j-2>=0&&m[i-1][j-1].getDisc()==p2.getName()) {
            if (m[i-1][j-1].getDisc()==p2.getName()&&m[i-2][j-2].getDisc()==p1.getName()){
                i=k;
                j=l;
                for (int n=0;n<=c;n++){
                    i--;
                    j--;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            i--;
            j--;
            c++;
        }
    }
    c=0;
    i=k;
    j=l;
    if(i>=2&&j<=size-3){
        while(i-2>=0&&j+2<=size-1&&m[i-1][j+1].getDisc()==p2.getName()){
            if (m[i-1][j+1].getDisc()==p2.getName()&&m[i-2][j+2].getDisc()==p1.getName()){
                i=k;
                j=l;
                for (int n=0;n<=c;n++){
                    i--;
                    j++;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            i--;
            j++;
            c++;
        }
    }
    c=0;
    i=k;
    j=l;
    if (i<=size-3&&j>=2){
        while (i+2<=size-1&&j-2>=0&&m[i+1][j-1].getDisc()==p2.getName()){
            if (m[i+1][j-1].getDisc()==p2.getName()&&m[i+2][j-2].getDisc()==p1.getName()){
                i=k;
                j=l;
                for (int n=0;n<=c;n++){
                    i++;
                    j--;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            i++;
            j--;
            c++;
        }
    }
    c=0;
    i=k;
    j=l;
    if(i<=size-3&&j<=size-3) {
        while (i+2<=size-1&&j+2<=size-1&&m[i + 1][j + 1].getDisc() == p2.getName()) {
            if (m[i+1][j+1].getDisc()==p2.getName()&&m[i+2][j+2].getDisc()==p1.getName()){
                i=k;
                j=l;
                for (int n=0;n<=c;n++){
                    i++;
                    j++;
                    m[i][j].setDisc(p1.getName());
                    b.putDisk(p1.getName(),i,j);
                    count++;
                }
                break;
            }
            i++;
            j++;
            c++;
        }
    }
    p1.getCount()=p1.getCount()+count;
    p2.getCount()=p2.getCount()-count+1;
    choise.clear();
    Disc disc('C', k, l);
    choise.push_back(disc);
}

Player * ReversiGameLogic::switchPlayer(Player *p, Player& p1, Player& p2){
    if(p->getName()=='X'){
        return &p2;
    }else{
        return &p1;
    }
}

void ReversiGameLogic::options(int i, int j, vector<Disc>& v){
    Disc a ('A',i,j);
    v.push_back(a);
}

vector <Disc>& ReversiGameLogic::getChoise(){
    return choise;
}