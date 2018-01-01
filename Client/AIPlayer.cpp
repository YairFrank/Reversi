// leah orlin 313357725
// yair frank 203699566

#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(): Player (){}

AIPlayer::AIPlayer(char x): Player(x){}


void AIPlayer::playTurn(Shortcuts::coordinate &coord, Shortcuts::coordVec &v,
                        Board &board, GameLogic &gamel, char &current, char &other, Client &cl, bool &firstMove, Shortcuts::PlayMessage &p) {
    GameLogic gl;
    Board dup;
    Shortcuts::coordVec flips, aiMoves = v;
    Shortcuts::coordVec::iterator it, it1;
    Shortcuts::coordinate c;
    Shortcuts::coordVec::iterator flipIt;
    Shortcuts::coordinate flip;
    Shortcuts::coordinate f;
    Shortcuts::matrix dupMatrix,b = board.getBoard();
    Shortcuts::aiOption option, bestOption;
    vector <Shortcuts::aiOption> options;
    vector <Shortcuts::aiOption> :: iterator optionsIt;
    int minScore = b.size() * b.size();	//maximum score possible

    cout << sign << ": I'm thinking... " << endl;

    for (it = aiMoves.begin(); it != aiMoves.end(); ++it) {
        c = *it;
        option.move = c;
        //we want to check each possible move in a new board, as if the others were not tried first.
        dup = Board(board);
        dup.enterMove(sign, c.x, c.y);
        dupMatrix = dup.getBoard();
        gl.flipTokens(sign, c.x - 1, c.y - 1, dupMatrix, flips);

        //flipping the tokens
        for (flipIt = flips.begin(); flipIt != flips.end(); ++flipIt) {
            flip = *flipIt;
            dup.enterMove(sign, flip.x + 1, flip.y + 1);
        }
        flips.clear();

        //get opponents best possible score given that AI made certain move, and store in "options" vector.
        option.score = getOpponentsBestOption(dup);	//fill in opponents best score for that movement option.
        options.push_back(option);
    }

    //find best option for AI player, after gaining data for all available options.
    for (optionsIt = options.begin(); optionsIt != options.end(); ++ optionsIt ) {
        option = *optionsIt;
        if (option.score < minScore) {
            minScore = option.score;
            bestOption = option;
        }
    }

    //set AI move to be the coordinates of the least advantageous to player.
    coord.x = bestOption.move.x;
    coord.y = bestOption.move.y;
    //alter board
    board.enterMove(current, coord.x, coord.y);

    gl.flipTokens(current, coord.x - 1, coord.y - 1, b, flips);
    for (it1 = flips.begin(); it1 != flips.end(); it1++) {
        f = *it1;
        board.enterMove(current, f.x + 1, f.y + 1);
    }
    flips.clear();
}

int AIPlayer::getOpponentsBestOption(Board b) {
    GameLogic gl;

    char oppSign = AIPlayer::getOppSign();
    vector<int> scores;
    int score = 0, bestScore;
    Shortcuts::coordVec oppPlayerMoves, flips;
    Shortcuts::matrix dup;
    Board dupBoard;
    Shortcuts::coordVec::iterator it, flipIt;
    Shortcuts::coordinate possibleMove, flip;

    //duplicate board - we don't want to change the original game board.
    dupBoard = Board(b);
    dup = dupBoard.getBoard();

    //the best score will be adapted later to opponents best possible score given AI move.
    bestScore = (dup.size() ^2) * -1;

    //get all of opponents possible moves, in order to check which will be least profitable for him/her.
    gl.getValidMoves(oppSign, oppPlayerMoves, dup);

    //check which possible move will be most profitable for opponent
    for (it = oppPlayerMoves.begin(); it != oppPlayerMoves.end(); ++it) {
        dupBoard = Board(b);
        possibleMove = *it;

        //enter possible AI move
        dupBoard.enterMove(oppSign,possibleMove.x, possibleMove.y);
        dup = dupBoard.getBoard();

        //flip what needs to be flipped
        gl.flipTokens(oppSign, possibleMove.x - 1, possibleMove.y - 1, dup, flips);
        for (flipIt = flips.begin(); flipIt != flips.end(); ++flipIt) {
            flip = *flipIt;
            dupBoard.enterMove(oppSign, flip.x + 1, flip.y + 1);
        }
        //clear vecor of coordinate that need to be flipped for next usage.
        flips.clear();

        // check score
        score = dupBoard.getScore(oppSign, sign);
        if (score > bestScore) {
            bestScore = score;
        }

    }
    return bestScore;
}

char AIPlayer::getOppSign() const {
    if (sign == 'O') {
        return 'X';
    }
    return 'O';
}