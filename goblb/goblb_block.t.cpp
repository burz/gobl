// goblb_block.t.cpp

#include <goblb_block.h>

#include <gtest/gtest.h>
#include <sstream>

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
        Space::Ptr space_p(new Space(0, 3, SpaceState::WHITE));
        block.addMember(space_p);
        EXPECT_EQ(1u, block.size());
        block.absorb(block);
        EXPECT_EQ(1u, block.size());
    }
    {
        Block block1;
        Space::Ptr space_p(new Space(9, 12, SpaceState::WHITE));
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
        Space::Ptr space_p(new Space(1, 2, SpaceState::WHITE));
        block.addMember(space_p);
        EXPECT_EQ(1u, block.size());
    }
    {
        Block block;
        {
            Space::Ptr space_p(new Space(3, 6, SpaceState::BLACK));
            block.addMember(space_p);
        }
        {
            Space::Ptr space_p(new Space(3, 8, SpaceState::BLACK));
            block.addMember(space_p);
        }
        EXPECT_EQ(2u, block.size());
    }
}

TEST(Block, libs)
{
    {
        Block block;
        EXPECT_EQ(0u, block.libs());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(1, 11));
        block.addLiberty(space_p);
        EXPECT_EQ(1u, block.libs());
    }
    {
        Block block;
        {
            Space::Ptr space_p(new Space(5, 4));
            block.addLiberty(space_p);
        }
        {
            Space::Ptr space_p(new Space(2, 1));
            block.addLiberty(space_p);
        }
        EXPECT_EQ(2u, block.libs());
    }
    {
        Block block;
        Space::Ptr space_p(new Space(18, 18));
        block.addLiberty(space_p);
        {
            Space::Ptr space_p(new Space(11, 14));
            block.addLiberty(space_p);
        }
        EXPECT_EQ(2u, block.libs());
        block.removeLiberty(space_p);
        EXPECT_EQ(1u, block.libs());
    }
}

TEST(Block, print)
{
    {
        const char RESULT[] = "<<(0, 4)>, <>>";

        Block block;
        Space::Ptr space_p(new Space(0, 4, SpaceState::BLACK));
        block.addMember(space_p);

        std::ostringstream stream;
        block.print(stream);
        EXPECT_STREQ(RESULT, stream.str().c_str());
    }
    {
        const char RESULT[] = "<<>, <(8, 9)>>";

        Block block;
        Space::Ptr space_p(new Space(8, 9));
        block.addLiberty(space_p);

        std::ostringstream stream;
        block.print(stream);
        EXPECT_STREQ(RESULT, stream.str().c_str());
    }
    {
        const char RESULT[] = "<<(1, 2)>, <(3, 4)>>";

        Block block;
        Space::Ptr space_p(new Space(1, 2, SpaceState::BLACK));
        block.addMember(space_p);
        space_p.reset(new Space(3, 4));
        block.addLiberty(space_p);

        std::ostringstream stream;
        block.print(stream);
        EXPECT_STREQ(RESULT, stream.str().c_str());
    }
}

TEST(Block, equals)
{
    Block block1;
    Block block2;
    EXPECT_TRUE(block1 == block2);
    EXPECT_FALSE(block1 != block2);

    Space::Ptr space_p(new Space(5, 4, SpaceState::WHITE));
    block1.addMember(space_p);
    EXPECT_FALSE(block1 == block2);
    EXPECT_TRUE(block1 != block2);

    block2.addMember(space_p);
    EXPECT_TRUE(block1 == block2);
    EXPECT_FALSE(block1 != block2);

    space_p.reset(new Space(5, 3));
    block2.addLiberty(space_p);
    EXPECT_FALSE(block1 == block2);
    EXPECT_TRUE(block1 != block2);

    block1.addLiberty(space_p);
    EXPECT_TRUE(block1 == block2);
    EXPECT_FALSE(block1 != block2);

    EXPECT_TRUE(block1 == block1);
}

} // Close goblb
