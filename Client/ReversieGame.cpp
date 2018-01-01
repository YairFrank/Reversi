/*
 * ReversieGame.cpp
 * yair frank 203699566
 * leah orlin 313357725
 */

#include "Shortcuts.h"
#include "ReversieGame.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

using namespace std;

ReversieGame::ReversieGame(int a) :
        gameOver(false), b(Board()), gl(GameLogic()), gameOption(a) {
}

void ReversieGame::play() {
    Player* p1;
    Player* p2;
    Client cl;
    char other;
    bool firstMove=true;
    if (gameOption == 1) {
        p1 = new HumanPlayer('X');
        p2 = new HumanPlayer('O');
    }
    if (gameOption == 2) {
        p1 = new HumanPlayer('X');
        p2 = new AIPlayer('O');
    }
    Shortcuts::matrix board;
    Player* current = p1;
    Shortcuts::coordVec p1v;
    Shortcuts::coordVec p2v;
    Shortcuts::coordVec v;
    Shortcuts::coordinate c;
    char winner;
    //if exits while loop - neither players have moves. Game over.
    board = b.getBoard();
    b.print();
    while (b.hasFreeSpaces()
           && (gl.hasValidMoves(p1->getSign(), p1v, board)
               || gl.hasValidMoves(p2->getSign(), p2v, board))) {
        if (p2v.empty()) {
            gl.hasValidMoves(p2->getSign(), p2v, board);
        }
        if (!p1v.empty()) {
            p1->setHasMoves(true);
        }
        if (p1v.empty()) {
            p1->setHasMoves(false);
        }
        if (!p2v.empty()) {
            p2->setHasMoves(true);
        }
        if (p2v.empty()) {
            p2->setHasMoves(false);
        }
        //set possible moves vector to be the either the vector of player1 or player 2.
        if (current->getHasMoves()) {
            if (current->getSign() == p1->getSign()) {
                v = p1v;
            } else {
                v = p2v;
            }
            char sign=current->getSign();
            Shortcuts::PlayMessage play;
            current->playTurn(c, v, b, gl, sign, other, cl, firstMove, play);
            p1v.clear();
            p2v.clear();
            board=b.getBoard();
        } else {
            //player had no moves available
            cout << "No possible moves for " << current->getSign()
                 << ". Play passes back to the other player" << endl;
        }
        //switch player
        if (current->getSign() == p1->getSign()) {
            current = p2;
        } else {
            current = p1;
        }
    }
    // neither player has valid moves available. Game over.
    //announce winner
    winner = ReversieGame::getWinner(p1, p2);
    if (winner == 't') {
        cout << "Game Over. You tied :-)" << endl;
    } else {
        cout << "Game Over. Winner is " << winner << " :)" << endl;
    }
    delete p1;
    delete p2;
}

char ReversieGame::getWinner(Player* p1, Player* p2) const {
    return b.getMaxPoints(p1->getSign(), p2->getSign());
}



