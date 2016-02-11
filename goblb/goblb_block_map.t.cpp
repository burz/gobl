// goblb_block_map.t.cpp

#include <goblb_block_map.h>

#include <gtest/gtest.h>
#include <map>
#include <set>
#include <sstream>

namespace goblb {

namespace {

void insertEmptyKoShape(
      BlockMap& blockMap
    , unsigned int i = 1
    , unsigned int j = 1
    , SpaceState::Value state = SpaceState::BLACK
)
{
    Block::Ptr block1(new Block());
    Space::Ptr space(new Space(i + 1, j, state));
    block1->addMember(space);

    Block::Ptr block2(new Block());
    space.reset(new Space(i - 1, j, state));
    block2->addMember(space);

    Block::Ptr block3(new Block());
    space.reset(new Space(i, j + 1, state));
    block3->addMember(space);

    Block::Ptr block4(new Block());
    space.reset(new Space(i, j - 1, state));
    block4->addMember(space);

    space.reset(new Space(i + 2, j, SpaceState::EMPTY));
    block1->addLiberty(space);

    space.reset(new Space(i - 2, j, SpaceState::EMPTY));
    block2->addLiberty(space);

    space.reset(new Space(i, j + 2, SpaceState::EMPTY));
    block3->addLiberty(space);

    space.reset(new Space(i, j - 2, SpaceState::EMPTY));
    block4->addLiberty(space);

    space.reset(new Space(i + 1, j + 1, SpaceState::EMPTY));
    block1->addLiberty(space);
    block3->addLiberty(space);

    space.reset(new Space(i - 1, j + 1, SpaceState::EMPTY));
    block2->addLiberty(space);
    block3->addLiberty(space);

    space.reset(new Space(i + 1, j - 1, SpaceState::EMPTY));
    block1->addLiberty(space);
    block4->addLiberty(space);

    space.reset(new Space(i - 1, j - 1, SpaceState::EMPTY));
    block2->addLiberty(space);
    block4->addLiberty(space);

    blockMap.insert(block1);
    blockMap.insert(block2);
    blockMap.insert(block3);
    blockMap.insert(block4);
}

class BlockMapRemoveValidator
{
  public:
    // TYPES
    typedef std::pair<std::set<Space::Ptr>, unsigned int> SpaceSetLiberties;
    typedef std::map<Block::Ptr, SpaceSetLiberties> LibertiesMap;

  private:
    // DATA
    BlockMap& d_blockMap;

    std::vector<Space::Ptr> d_spaces;
    LibertiesMap            d_exterior;

  public:
    // CREATORS
    BlockMapRemoveValidator(BlockMap& blockMap)
    : d_blockMap(blockMap)
    {
    }

  private:
    // PRIVATE MANIPULATORS
    void setupBlock(
          Block::Ptr adjacentBlock_p
        , const Space::Ptr& space_p
    )
    {
        if(adjacentBlock_p)
        {
            SpaceState::Value adjacentState = adjacentBlock_p->state();

            if(space_p->state() != adjacentState)
            {
                ASSERT_LT(0u, adjacentBlock_p->libs());

                LibertiesMap::iterator pos =
                    d_exterior.find(adjacentBlock_p);

                if(d_exterior.end() != pos)
                {
                    pos->second.first.insert(space_p);
                }
                else
                {
                    d_exterior.insert(LibertiesMap::value_type(
                          adjacentBlock_p
                        , SpaceSetLiberties(
                              std::set<Space::Ptr>({space_p})
                            , adjacentBlock_p->libs()
                          )
                    ));
                }
            }
        }
    }

    void setup(const Block::Ptr& block_p)
    {
        ASSERT_TRUE(static_cast<bool>(block_p));

        for(auto itt = block_p->members().begin()
          ; block_p->members().end() != itt
          ; ++itt)
        {
            d_spaces.push_back(*itt);

            setupBlock(
                  d_blockMap.lookup((*itt)->i() + 1, (*itt)->j())
                , *itt
            );
            setupBlock(
                  d_blockMap.lookup((*itt)->i() - 1, (*itt)->j())
                , *itt
            );
            setupBlock(
                  d_blockMap.lookup((*itt)->i(), (*itt)->j() + 1)
                , *itt
            );
            setupBlock(
                  d_blockMap.lookup((*itt)->i(), (*itt)->j() - 1)
                , *itt
            );
        }
    }

    void runValidation()
    {
        for(auto itt = d_spaces.begin(); itt != d_spaces.end(); ++itt)
        {
            EXPECT_EQ(SpaceState::EMPTY, (*itt)->state());
        }

        for(auto itt = d_exterior.begin(); itt != d_exterior.end(); ++itt)
        {
            const unsigned int membersTouching = itt->second.first.size();
            const unsigned int blockLiberties = itt->second.second;

            EXPECT_EQ(blockLiberties + membersTouching, itt->first->libs());
        }
    }

  public:
    // MANIPULATORS
    void validate(const Block::Ptr& block_p)
    {
        setup(block_p);

        std::cout << "!!! BEFORE:" << std::endl
                  << d_blockMap << std::endl;

        d_blockMap.remove(block_p);

        std::cout << "!!! AFTER:" << std::endl
                  << d_blockMap << std::endl;

        runValidation();
    }
};

} // Close anonymous

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

TEST(BlockMap, removeSingleSpace)
{
    {
        BlockMap map;

        Space::Ptr space(new Space(7, 3, SpaceState::BLACK));
        Block::Ptr block(new Block());
        block->addMember(space);
        map.insert(block);

        BlockMapRemoveValidator validator(map);

        validator.validate(block);
    }
    {
        BlockMap map;

        {
            Block::Ptr block(new Block());
            {
                Space::Ptr space(new Space(7, 4, SpaceState::WHITE));
                block->addMember(space);
            }
            {
                Space::Ptr space(new Space(7, 5));
                block->addLiberty(space);
            }
            {
                Space::Ptr space(new Space(8, 4));
                block->addLiberty(space);
            }
            {
                Space::Ptr space(new Space(6, 4));
                block->addLiberty(space);
            }
            map.insert(block);
        }

        Block::Ptr block(new Block());
        Space::Ptr space(new Space(7, 3, SpaceState::BLACK));
        block->addMember(space);

        BlockMapRemoveValidator validator(map);

        validator.validate(block);
    }
    {
        BlockMap map;

        insertEmptyKoShape(map, 4, 4);

        Block::Ptr block(new Block());
        Space::Ptr space(new Space(4, 4, SpaceState::WHITE));
        block->addMember(space);
        map.insert(block);

        BlockMapRemoveValidator validator(map);

        validator.validate(block);
    }
}

TEST(BlockMap, removeTwoSpaces)
{
    {
        BlockMap map;

        insertEmptyKoShape(map, 2, 2);
        insertEmptyKoShape(map, 7, 2);

        {
            Block::Ptr block(new Block());
            Space::Ptr space(new Space(4, 3, SpaceState::BLACK));
            block->addMember(space);
            space.reset(new Space(5, 3, SpaceState::BLACK));
            block->addMember(space);
            space.reset(new Space(4, 4));
            block->addLiberty(space);
            space.reset(new Space(5, 4));
            block->addLiberty(space);
            space.reset(new Space(6, 3));
            block->addLiberty(space);
            space.reset(new Space(3, 3));
            block->addLiberty(space);
            map.insert(block);
        }

        Block::Ptr block(new Block());
        Space::Ptr space(new Space(4, 2, SpaceState::WHITE));
        block->addMember(space);
        space.reset(new Space(5, 2, SpaceState::WHITE));
        block->addMember(space);

        BlockMapRemoveValidator validator(map);

        validator.validate(block);
    }
}

TEST(BlockMap, print)
{
    BlockMap map;

    insertEmptyKoShape(map, 4, 4);

    std::ostringstream stream;

    map.print(stream);

    std::cout << "!!! GOT" << std::endl
              << stream.str() << std::endl;

    static const char MAP[] =
        "\n 5  [  EMPTY    3B   EMPTY ]\n"
          " 4  [    3B   EMPTY    3B  ]\n"
          " 3  [  EMPTY    3B   EMPTY ]\n"
          "         3      4      5\n";

    std::cout << "!!! EXPECTED:" << std::endl
              << MAP << std::endl;

    EXPECT_STREQ(MAP, stream.str().c_str());
}

} // Close goblb
