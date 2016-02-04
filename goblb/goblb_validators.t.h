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
#include <set>

namespace goblb {

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

} // Close goblb

#endif
