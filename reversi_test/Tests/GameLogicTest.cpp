//
// leah orlin 313357725
// yair frank 203699566

#include <gtest/gtest.h>
#include <Board.h>
#include <HumanPlayer.h>

TEST(GameLogic___Test, LogicFunctions){
    Board b;
    GameLogic gl;
    HumanPlayer a('O');
    b.enterMove('O',3,5);
    b.enterMove('O',4,5);
    b.enterMove('X',4,3);
    b.enterMove('X',4,4);
    b.enterMove('X',5,5);
    b.enterMove('X',6,6);
    Shortcuts::matrix board;
    Shortcuts::coordVec p2v;
    Shortcuts::coordVec flips;
    Shortcuts::coordVec::iterator it;
    Shortcuts::coordinate c, f;
    board = b.getBoard();
    gl.hasValidMoves(a.getSign(), p2v, board);
    ASSERT_EQ(p2v.size(), 4);
    ASSERT_EQ(p2v[0].x, 5);
    ASSERT_EQ(p2v[0].y, 3);
    ASSERT_EQ(p2v[1].x, 4);
    ASSERT_EQ(p2v[1].y, 2);
    ASSERT_EQ(p2v[2].x, 6);
    ASSERT_EQ(p2v[2].y, 3);
    ASSERT_EQ(p2v[3].x, 6);
    ASSERT_EQ(p2v[3].y, 5);
    b.enterMove('O',6,5);
    gl.flipTokens('O', 5, 4, board, flips);
    ASSERT_EQ(flips.size(), 1);
    ASSERT_EQ(flips[0].x, 4);
    ASSERT_EQ(flips[0].y, 4);
}