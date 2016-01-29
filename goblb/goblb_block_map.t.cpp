// goblb_block_map.t.cpp

#include <goblb_block_map.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(BlockMap, constructor)
{
    BlockMap map;
}

TEST(BlockMap, lookup)
{
    {
        BlockMap map;
        Block::Ptr block = map.lookup(12, 3);
        EXPECT_FALSE(static_cast<bool>(block));
    }
    {
        BlockMap map;

        Space::Ptr space(new Space(7, 3, SpaceState::BLACK));
        Block::Ptr block(new Block());
        block->addMember(space);

        map.insert(block);

        Block::Ptr returnedBlock = map.lookup(7, 3);
        EXPECT_TRUE(static_cast<bool>(returnedBlock));
        EXPECT_EQ(block, returnedBlock);
    }
    {
        BlockMap map;

        Space::Ptr space(new Space(7, 3, SpaceState::BLACK));
        Block::Ptr block(new Block());
        block->addMember(space);

        map.insert(block);

        block = map.lookup(7, 3);
        EXPECT_TRUE(static_cast<bool>(block));

        map.remove(block);

        block = map.lookup(7, 3);
        EXPECT_FALSE(static_cast<bool>(block));
    }
}

} // Close goblb
