//
// leah orlin 313357725
// yair frank 203699566

#include <gtest/gtest.h>
#include "Board.h"

TEST(Board__Test, Construction){
    Board b;
    ASSERT_EQ(b.getBoard()[0][0], ' ');
    ASSERT_EQ(b.getBoard()[0][1], ' ');
    ASSERT_EQ(b.getBoard()[1][0], ' ');
    ASSERT_EQ(b.getBoard()[1][1], ' ');
}
TEST(Board__Test, construction2__score_maxpoints) {
    Board b (4);
    for(int i=1;i<2;i++)
        for(int j=1;j<5;j++)
            b.enterMove('A',i,j);
    for(int i=2;i<5;i++)
        for(int j=1;j<5;j++)
            b.enterMove('B',i,j);
    ASSERT_EQ(b.getBoard()[0][0], 'A');
    ASSERT_EQ(b.getBoard()[0][1], 'A');
    ASSERT_EQ(b.getBoard()[1][0], 'B');
    ASSERT_EQ(b.getBoard()[1][1], 'B');
    ASSERT_EQ(b.getMaxPoints('A','B'), 'B');
    ASSERT_EQ(b.getScore('B','A'), 8);
}
TEST(Board__Test, SetMove){
    Board b;
    b.enterMove('!',1,1);
    b.enterMove('@',1,2);
    b.enterMove('#',2,1);
    b.enterMove('$',2,2);
    ASSERT_EQ(b.getBoard()[0][0], '!');
    ASSERT_EQ(b.getBoard()[0][1], '@');
    ASSERT_EQ(b.getBoard()[1][0], '#');
    ASSERT_EQ(b.getBoard()[1][1], '$');
}