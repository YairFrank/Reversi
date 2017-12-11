//
// leah orlin 313357725
// yair frank 203699566

#include <gtest/gtest.h>
#include <HumanPlayer.h>

TEST(Player__Test, GeneralTest){
    HumanPlayer h('A');
    h.setHasMoves(true);
    ASSERT_EQ(h.getHasMoves(), true);
    ASSERT_EQ(h.getSign(), 'A');
}