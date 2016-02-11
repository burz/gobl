// gobls_sgf.t.cpp

#include <gobls_sgf.h>
#include <goblu_exception.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(Sgf, makeIsPass)
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

TEST(Sgf, constructor)
{
    Sgf sgf;
}

TEST(Sgf, addLookupMetadata)
{
    Sgf sgf;

    sgf.add("hello", "world!");
    EXPECT_EQ("world!", sgf.lookup("hello"));

    EXPECT_THROW(sgf.lookup("oops"), goblu::Exception);
}

TEST(Sgf, addIterateMoves)
{
    Sgf sgf;

    EXPECT_EQ(sgf.end(), sgf.begin());

    sgf.add(0, 1);

    EXPECT_NE(sgf.end(), sgf.begin());
    EXPECT_EQ(Sgf::Move(0, 1), *sgf.begin());
}

} // Close gobls
