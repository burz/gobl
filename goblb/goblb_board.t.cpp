// goblb_board.t.cpp

#include <goblb_board.h>

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

namespace goblb {

TEST(Board, constructor)
{
    Board board;

    for(unsigned int i = 0; i < Board::SIZE; ++i)
    {
        for(unsigned int j = 0; j < Board::SIZE; ++j)
        {
            ASSERT_TRUE(static_cast<bool>(board.space(i, j)));
            EXPECT_EQ(SpaceState::EMPTY, board.space(i, j)->state());
        }
    }
}

TEST(Board, setState)
{
    Board board;

    for(unsigned int i = 0; i < Board::SIZE; ++i)
    {
        for(unsigned int j = 0; j < Board::SIZE; ++j)
        {
            board.setState(i, j, SpaceState::BLACK);
            EXPECT_EQ(SpaceState::BLACK, board.state(i, j));
            board.setState(i, j, SpaceState::WHITE);
            EXPECT_EQ(SpaceState::WHITE, board.state(i, j));
            board.setState(i, j, SpaceState::EMPTY);
            EXPECT_EQ(SpaceState::EMPTY, board.state(i, j));
        }
    }
}

TEST(Board, print)
{
    std::ostringstream lineStream;
    lineStream << "  [ EMPTY";
    for(unsigned int i = 1; i < Board::SIZE; ++i)
    {
        lineStream << ", EMPTY";
    }
    lineStream << " ]\n";

    std::string line = lineStream.str();

    std::ostringstream expectedStream;
    for(unsigned int i = 1; i <= Board::SIZE; ++i)
    {
        const unsigned int k = Board::SIZE - i;

        expectedStream << std::setw(2) << k << line;
    }
    expectedStream << "     ";
    for(unsigned int j = 0; j < Board::SIZE; ++j)
    {
        expectedStream << "  " << std::setw(2) << j << "   ";
    }
    expectedStream << std::endl;

    std::ostringstream outStream;

    Board board;

    board.print(outStream);

    std::cout << "!!! EXPECTED:" << std::endl << expectedStream.str()
              << "!!! GOT:" << std::endl << outStream.str()
              << std::endl;

    EXPECT_STREQ(expectedStream.str().c_str(), outStream.str().c_str());
}

TEST(Board, equals)
{
    Board board1;

    EXPECT_TRUE(board1 == board1);

    Board board2;

    EXPECT_TRUE(board1 == board2);
    EXPECT_FALSE(board1 != board2);
    board1.setState(0, 0, SpaceState::BLACK);
    EXPECT_FALSE(board1 == board2);
    EXPECT_TRUE(board1 != board2);
    board2.setState(0, 0, SpaceState::WHITE);
    EXPECT_FALSE(board1 == board2);
    EXPECT_TRUE(board1 != board2);
    board2.setState(0, 0, SpaceState::BLACK);
    EXPECT_TRUE(board1 == board2);
    EXPECT_FALSE(board1 != board2);
    board2.setState(3, 5, SpaceState::BLACK);
    EXPECT_FALSE(board1 == board2);
    EXPECT_TRUE(board1 != board2);

    EXPECT_TRUE(board1 == board1);
}

TEST(Board, nextMove)
{
    Board board;

    EXPECT_EQ(SpaceState::BLACK, board.nextMove());

    board.play(12, 1);

    EXPECT_EQ(SpaceState::WHITE, board.nextMove());

    board.play(3, 4);

    EXPECT_EQ(SpaceState::BLACK, board.nextMove());
}

TEST(Board, playCaptureCorner)
{
    Board board;

    board.play(0, 1);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::BLACK, board.state(0, 1));

    Block::Ptr block1_p = board.lookupBlock(0, 1);
    EXPECT_TRUE(static_cast<bool>(block1_p));
    EXPECT_EQ(3u, block1_p->libs());

    board.play(0, 0);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::WHITE, board.state(0, 0));

    Block::Ptr block2_p = board.lookupBlock(0, 0);
    EXPECT_TRUE(static_cast<bool>(block2_p));
    EXPECT_EQ(1u, block2_p->libs());
    EXPECT_EQ(2u, block1_p->libs());

    board.play(1, 0);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::BLACK, board.state(1, 0));

    Block::Ptr block3_p = board.lookupBlock(1, 0);
    EXPECT_TRUE(static_cast<bool>(block3_p));
    EXPECT_EQ(3u, block3_p->libs());
    EXPECT_EQ(3u, block1_p->libs());

    block2_p = board.lookupBlock(0, 0);
    EXPECT_FALSE(static_cast<bool>(block2_p));
    EXPECT_EQ(SpaceState::EMPTY, board.state(0, 0));
}

} // Close goblb
