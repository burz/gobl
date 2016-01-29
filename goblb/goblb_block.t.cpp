// goblb_block.t.cpp

#include <goblb_block.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(Block, constructor)
{
    Block block;
}

TEST(Block, size)
{
    {
        Block block;
        EXPECT_EQ(0u, block.size());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(2, 1));
        block.addMember(space_p);
        EXPECT_EQ(1u, block.size());
    }
    {
        Block block;
        {
            Space::Ptr space_p(new Space(1, 3));
            block.addMember(space_p);
        }
        {
            Space::Ptr space_p(new Space(3, 3));
            block.addMember(space_p);
        }
        EXPECT_EQ(2u, block.size());
    }
}

TEST(Block, liberties)
{
    {
        Block block;
        EXPECT_EQ(0u, block.liberties());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(2, 1));
        block.addLiberty(space_p);
        EXPECT_EQ(1u, block.liberties());
    }
    {
        Block block;
        {
            Space::Ptr space_p(new Space(1, 3));
            block.addLiberty(space_p);
        }
        {
            Space::Ptr space_p(new Space(3, 3));
            block.addLiberty(space_p);
        }
        EXPECT_EQ(2u, block.liberties());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(1, 3));
        block.addLiberty(space_p);
        {
            Space::Ptr space_p(new Space(3, 3));
            block.addLiberty(space_p);
        }
        EXPECT_EQ(2u, block.liberties());
        block.removeLiberty(space_p);
        EXPECT_EQ(1u, block.liberties());
    }
}

} // Close goblb