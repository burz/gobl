// goblb_validators.t.h
#ifndef INCLUDED_GOBLB_VALIDATORS_T
#define INCLUDED_GOBLB_VALIDATORS_T

#ifndef INCLUDED_GOBLB_BLOCK
#include <goblb_block.h>
#endif

#ifndef INCLUDED_GOBLB_BLOCK_MAP
#include <goblb_block_map.h>
#endif

#ifndef INCLUDED_GOBLB_SPACE
#include <goblb_space.h>
#endif

#include <gtest/gtest.h>
#include <map>

namespace goblb {

class BlockMapRemoveValidator
{
  public:
    // TYPES
    typedef std::map<Block::Ptr, unsigned int> LibertiesMap;

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
        , SpaceState::Value blockState
    )
    {
        if(adjacentBlock_p)
        {
            ASSERT_LT(0u, adjacentBlock_p->size());
            
            SpaceState::Value adjacentState =
                (*adjacentBlock_p->members().begin())->state();

            if(blockState != adjacentState)
            {
                ASSERT_LT(0u, adjacentBlock_p->libs());

                d_exterior.insert(LibertiesMap::value_type(
                      adjacentBlock_p
                    , adjacentBlock_p->libs()
                ));
            }
        }
    }

    void setup(const Block::Ptr& block_p)
    {
        ASSERT_TRUE(static_cast<bool>(block_p));
        ASSERT_LT(0u, block_p->size());

        SpaceState::Value blockState = (*block_p->members().begin())->state();

        for(auto itt = block_p->members().begin()
          ; block_p->members().end() != itt
          ; ++itt)
        {
            d_spaces.push_back(*itt);

            setupBlock(
                  d_blockMap.lookup((*itt)->i() + 1, (*itt)->j())
                , blockState
            );
            setupBlock(
                  d_blockMap.lookup((*itt)->i() - 1, (*itt)->j())
                , blockState
            );
            setupBlock(
                  d_blockMap.lookup((*itt)->i(), (*itt)->j() + 1)
                , blockState
            );
            setupBlock(
                  d_blockMap.lookup((*itt)->i(), (*itt)->j() - 1)
                , blockState
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
            EXPECT_EQ(itt->second + 1, itt->first->libs());
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

} // Close goblb

#endif
