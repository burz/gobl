// gobld_game.t.cpp

#include <gobld_game.h>
#include <gobls_parser.h>
#include <goblu_exception.h>

#include <gtest/gtest.h>

namespace gobld {

TEST(Game, constructor)
{
    gobls::Sgf::Ptr sgf_p(new gobls::Sgf());

    Game game(sgf_p);

    EXPECT_THROW(game.metadata("A"), goblu::Exception);

    std::cout << game << std::endl;

    EXPECT_FALSE(game.next());
}

TEST(Game, simpleGame)
{
    gobls::Sgf::Ptr sgf_p = gobls::Parser::parseString("(;A[B];B[aa];W[gg])");

    Game game(sgf_p);

    EXPECT_EQ("B", game.metadata("A"));
    EXPECT_THROW(game.metadata("C"), goblu::Exception);

    std::cout << game << std::endl;

    EXPECT_TRUE(game.next());

    std::cout << game << std::endl;

    EXPECT_TRUE(game.next());

    std::cout << game << std::endl;

    EXPECT_FALSE(game.next());
}

} // Close gobld
