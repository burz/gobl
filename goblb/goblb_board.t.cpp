// goblb_board.t.cpp

#include <goblb_board.h>

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

namespace goblb {

TEST(Board, constructor)
{
    Board board;
    static const unsigned int size = Board::SIZE;
    EXPECT_EQ(size, board.size());

    for(unsigned int i = 0; i < size; ++i)
    {
        for(unsigned int j = 0; j < size; ++j)
        {
            ASSERT_TRUE(static_cast<bool>(board.space(i, j)));
            EXPECT_EQ(SpaceState::EMPTY, board.space(i, j)->state());
        }
    }

    EXPECT_EQ(SpaceState::BLACK, board.nextMove());
    EXPECT_EQ(0, board.score());
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

TEST(Board, playGroupFriends)
{
    Board board;

    board.play(6, 6, SpaceState::BLACK);

    std::cout << board << std::endl;

    Block::Ptr block_p = board.block(6, 6);
    ASSERT_TRUE(static_cast<bool>(block_p));

    std::cout << *block_p << std::endl;

    EXPECT_EQ(4u, block_p->libs());

    board.play(6, 7, SpaceState::BLACK);

    std::cout << board << std::endl;

    block_p = board.block(6, 6);

    std::cout << *block_p << std::endl;

    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(6u, block_p->libs());

    block_p = board.block(6, 7);

    std::cout << *block_p << std::endl;

    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(6u, block_p->libs());
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

    Block::Ptr block1_p = board.block(0, 1);
    ASSERT_TRUE(static_cast<bool>(block1_p));
    EXPECT_EQ(3u, block1_p->libs());

    board.play(0, 0);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::WHITE, board.state(0, 0));

    Block::Ptr block2_p = board.block(0, 0);
    ASSERT_TRUE(static_cast<bool>(block2_p));
    EXPECT_EQ(1u, block2_p->libs());
    EXPECT_EQ(2u, block1_p->libs());

    board.play(1, 0);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::BLACK, board.state(1, 0));

    Block::Ptr block3_p = board.block(1, 0);
    ASSERT_TRUE(static_cast<bool>(block3_p));
    EXPECT_EQ(3u, block3_p->libs());
    EXPECT_EQ(3u, block1_p->libs());

    block2_p = board.block(0, 0);
    EXPECT_FALSE(static_cast<bool>(block2_p));
    EXPECT_EQ(SpaceState::EMPTY, board.state(0, 0));

    EXPECT_EQ(-1, board.score());
}

TEST(Board, playCornerFriends)
{
    Board board;

    board.play(0, 0);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::BLACK, board.state(0, 0));

    Block::Ptr block_p = board.block(0, 0);
    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(2u, block_p->libs());

    board.play(13, 13);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::WHITE, board.state(13, 13));

    block_p = board.block(13, 13);
    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(4u, block_p->libs());
    EXPECT_EQ(2u, board.block(0, 0)->libs());

    board.play(1, 0);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::BLACK, board.state(1, 0));

    block_p = board.block(1, 0);
    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(3u, block_p->libs());
    EXPECT_EQ(4u, board.block(13, 13)->libs());
    EXPECT_EQ(3u, board.block(0, 0)->libs());

    board.play(13, 11);

    std::cout << board << std::endl;

    EXPECT_EQ(SpaceState::WHITE, board.state(13, 11));

    block_p = board.block(13, 11);
    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(4u, block_p->libs());
    EXPECT_EQ(4u, board.block(13, 13)->libs());
    EXPECT_EQ(3u, board.block(1, 0)->libs());
    EXPECT_EQ(3u, board.block(0, 0)->libs());

    board.play(0, 1);

    std::cout << board << std::endl;
    board.printBlockMap(std::cout);
    std::cout << std::endl;

    EXPECT_EQ(SpaceState::BLACK, board.state(0, 1));

    block_p = board.block(0, 1);
    ASSERT_TRUE(static_cast<bool>(block_p));
    EXPECT_EQ(3u, block_p->libs());
    EXPECT_EQ(4u, board.block(13, 11)->libs());
    EXPECT_EQ(4u, board.block(13, 13)->libs());
    EXPECT_EQ(3u, board.block(1, 0)->libs());
    EXPECT_EQ(3u, board.block(0, 0)->libs());

    EXPECT_EQ(0, board.score());
}

TEST(Board, playCaptureBigGroup)
{
    Board board;

    board.play(9, 9, SpaceState::BLACK);
    board.play(9, 10, SpaceState::BLACK);
    board.play(9, 11, SpaceState::BLACK);
    board.play(10, 9, SpaceState::BLACK);
    board.play(10, 10, SpaceState::BLACK);
    board.play(10, 11, SpaceState::BLACK);
    board.play(11, 9, SpaceState::BLACK);
    board.play(11, 10, SpaceState::BLACK);
    board.play(11, 11, SpaceState::BLACK);

    std::cout << "START" << std::endl << board << std::endl;
    board.printBlockMap(std::cout);
    std::cout << std::endl;

    EXPECT_EQ(9u, board.block(10, 10)->size());
    EXPECT_EQ(12u, board.block(10, 10)->libs());

    EXPECT_EQ(12u, board.block(9, 9)->libs());
    EXPECT_EQ(12u, board.block(9, 10)->libs());
    EXPECT_EQ(12u, board.block(9, 11)->libs());
    EXPECT_EQ(12u, board.block(10, 9)->libs());
    EXPECT_EQ(12u, board.block(10, 10)->libs());
    EXPECT_EQ(12u, board.block(10, 11)->libs());
    EXPECT_EQ(12u, board.block(11, 9)->libs());
    EXPECT_EQ(12u, board.block(11, 10)->libs());
    EXPECT_EQ(12u, board.block(11, 11)->libs());

    board.play(8, 9, SpaceState::WHITE);
    board.play(8, 10, SpaceState::WHITE);
    board.play(8, 11, SpaceState::WHITE);
    board.play(9, 8, SpaceState::WHITE);
    board.play(10, 8, SpaceState::WHITE);
    board.play(11, 8, SpaceState::WHITE);
    board.play(9, 12, SpaceState::WHITE);
    board.play(10, 12, SpaceState::WHITE);
    board.play(11, 12, SpaceState::WHITE);
    board.play(12, 9, SpaceState::WHITE);
    board.play(12, 10, SpaceState::WHITE);

    EXPECT_EQ(9u, board.block(10, 10)->size());
    EXPECT_EQ(1u, board.block(10, 10)->libs());

    board.play(12, 11, SpaceState::WHITE);

    std::cout << "END" << std::endl << board << std::endl;
    board.printBlockMap(std::cout);
    std::cout << std::endl;
}

TEST(Board, playKo)
{
    Board board;

    EXPECT_FALSE(static_cast<bool>(board.ko()));

    board.play(0, 0);
    board.play(1, 0);
    board.play(1, 1);
    board.play(4, 1);
    board.play(0, 2);

    std::cout << board << std::endl;

    EXPECT_FALSE(static_cast<bool>(board.ko()));

    board.play(0, 1);

    std::cout << board << std::endl;

    EXPECT_TRUE(static_cast<bool>(board.ko()));
    EXPECT_EQ(board.space(0, 0), board.ko());

    board.play(0, 0);

    std::cout << board << std::endl;

    EXPECT_TRUE(static_cast<bool>(board.ko()));
    EXPECT_EQ(board.space(0, 1), board.ko());
}

} // Close goblb
