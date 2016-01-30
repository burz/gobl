// gobls_sgf.t.cpp

#include <gobls_sgf.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(Sgf, constructor)
{
    Sgf sgf;
}

TEST(Sgf, isPass)
{
    {
        Sgf::Move move;
        EXPECT_FALSE(Sgf::isPass(move));
    }
    {
        Sgf::Move move = Sgf::makePass();
        EXPECT_TRUE(Sgf::isPass(move));
    }
}

} // Close gobls
