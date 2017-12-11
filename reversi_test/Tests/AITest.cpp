//
// leah orlin 313357725
// yair frank 203699566

#include <gtest/gtest.h>
#include <Board.h>
#include <HumanPlayer.h>
#include <AIPlayer.h>

TEST(AI__Test, game){
    Board b;
    b.enterMove('X',3,4);
    b.enterMove('X',4,4);
    AIPlayer a ('O');
    Shortcuts::matrix board;
    Shortcuts::coordVec p2v;
    Shortcuts::coordVec v, flips;
    Shortcuts::coordVec::iterator it;
    Shortcuts::coordinate c, f;
    board = b.getBoard();
    GameLogic gl;
    char curr, oth;
    Client cl;
    bool first;
    gl.hasValidMoves(a.getSign(), p2v, board);
    a.playTurn(c,p2v,b, gl, curr, oth, cl, first);
    b.enterMove(a.getSign(), c.x, c.y);
    gl.flipTokens(a.getSign(), c.x - 1, c.y - 1, board, flips);
    for (it = flips.begin(); it != flips.end(); it++) {
        f = *it;
        b.enterMove(a.getSign(), f.x + 1, f.y + 1);
    }
    ASSERT_EQ(b.getBoard()[2][2], 'O');
    ASSERT_EQ(a.getOpponentsBestOption(b), 3);
}