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

        Block::Ptr block(new Block());
        map.insert(7, 3, block);

        Block::Ptr returnedBlock = map.lookup(7, 3);
        EXPECT_TRUE(static_cast<bool>(returnedBlock));
        EXPECT_EQ(block, returnedBlock);
    }
    {
        BlockMap map;

        Block::Ptr block(new Block());
        map.insert(7, 3, block);

        block = map.lookup(7, 3);
        EXPECT_TRUE(static_cast<bool>(block));

        map.remove(7, 3);

        block = map.lookup(7, 3);
        EXPECT_FALSE(static_cast<bool>(block));
    }
}

} // Close goblb
