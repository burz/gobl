// goblb_block.t.cpp

#include <goblb_block.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(Block, constructor)
{
    Block block;
}

TEST(Block, absorb)
{
    {
        Block block1;
        EXPECT_EQ(0u, block1.size());
        Block block2;
        EXPECT_EQ(0u, block2.size());
        block1.absorb(block2);
        EXPECT_EQ(0u, block1.size());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(SpaceState::WHITE));
        block.addMember(space_p);
        EXPECT_EQ(1u, block.size());
        block.absorb(block);
        EXPECT_EQ(1u, block.size());
    }
    {
        Block block1;
        Space::Ptr space_p(new Space(SpaceState::WHITE));
        block1.addMember(space_p);
        EXPECT_EQ(1u, block1.size());
        Block block2;
        EXPECT_EQ(0u, block2.size());
        block2.absorb(block1);
        EXPECT_EQ(1u, block2.size());
    }
}

TEST(Block, size)
{
    {
        Block block;
        EXPECT_EQ(0u, block.size());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(SpaceState::WHITE));
        block.addMember(space_p);
        EXPECT_EQ(1u, block.size());
    }
    {
        Block block;
        {
            Space::Ptr space_p(new Space(SpaceState::BLACK));
            block.addMember(space_p);
        }
        {
            Space::Ptr space_p(new Space(SpaceState::BLACK));
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
        Space::Ptr space_p(new Space());
        block.addLiberty(space_p);
        EXPECT_EQ(1u, block.liberties());
    }
    {
        Block block;
        {
            Space::Ptr space_p(new Space());
            block.addLiberty(space_p);
        }
        {
            Space::Ptr space_p(new Space());
            block.addLiberty(space_p);
        }
        EXPECT_EQ(2u, block.liberties());
    }
    {
        Block block;
        Space::Ptr space_p(new Space());
        block.addLiberty(space_p);
        {
            Space::Ptr space_p(new Space());
            block.addLiberty(space_p);
        }
        EXPECT_EQ(2u, block.liberties());
        block.removeLiberty(space_p);
        EXPECT_EQ(1u, block.liberties());
    }
}

} // Close goblb
