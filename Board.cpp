//
// Created by yair on 25/10/17.
//

//Yair Frank 203699566

#include "Board.h"
#include <iostream>

using namespace std;

Board::Board (int size): size(size) {
    buildMatrix();
    fillMatrix ();
}

void Board::buildMatrix() {
    matrix = new Disc* [size];
    for (int i=0; i<size; i++)
        matrix [i] = new Disc[size];
}

void Board::fillMatrix(){
    matrix [size/2-1] [size/2-1].setDisc('O');
    matrix [size/2] [size/2].setDisc('O');
    matrix [size/2-1] [size/2].setDisc('X');
    matrix [size/2] [size/2-1].setDisc('X');
    for (int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(matrix [i][j].getDisc()=='0')
                matrix [i][j].setDisc(' ');
}

void Board::print() const {
    cout<<"Current board:"<<endl<<endl;
    cout<<"   ";
    for (int i=1;i<=size;i++){
        if (i==1)
            cout<<"| "<<i<<" |";
        else
            cout<<" "<<i<<" |";
    }
    cout<<endl;
    for (int l=0;l<=size;l++)
        cout<<"----";
    cout<<endl;
    for (int i=1;i<=size;i++) {
        for (int j = -1; j < size; j++){
            if(j==-1)
                cout<<" "<<i<<" |";
            else
                cout  <<" "<<matrix[i-1][j].getDisc()<< " |";
        }
        cout << endl;
        for (int l=0;l<=size;l++)
            cout<<"----";
        cout<<endl;
    }
}

Disc** Board::getBoard (){
    return matrix;
}

void Board::putDisk (char disc, int row, int column){
    matrix [row] [column].setDisc(disc);
}

Board::~Board() {
    for(int i=0; i< size; i++)
        delete [] matrix[i];
    delete [] matrix;
}