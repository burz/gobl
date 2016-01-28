// goblb_board.t.cpp

#include <goblb_board.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(Board, constructor)
{
    Board board;

    for(unsigned int i = 0; i < Board::BOARD_SIZE; ++i)
    {
        for(unsigned int j = 0; j < Board::BOARD_SIZE; ++j)
        {
            ASSERT_TRUE(static_cast<bool>(board.space(i, j)));
            EXPECT_EQ(SpaceState::EMPTY, board.space(i, j)->state());
        }
    }
}

} // Close goblb
