// goblb_block_map.cpp

#include <goblb_block_map.h>
#include <goblb_board.h>

#include <cassert>

namespace goblb {

void BlockMap::insert(const Block::Ptr& block_p)
{
    for(auto itt = block_p->members().begin()
      ; itt != block_p->members().end()
      ; ++itt)
    {
        const Space::Ptr& space_p = *itt;

        d_map.insert(Map::value_type(
              Coordinates(space_p->i(), space_p->j())
            , block_p
        ));
    }
}

void BlockMap::remove(const Block::Ptr& block_p)
{
    for(auto itt = block_p->members().begin()
      ; itt != block_p->members().end()
      ; ++itt)
    {
        const Space::Ptr& space_p = *itt;

        d_map.erase(Coordinates(space_p->i(), space_p->j()));

        space_p->setState(SpaceState::EMPTY);
    }
}

Block::Ptr BlockMap::lookup(unsigned int i, unsigned int j) const
{
    assert(i < Board::SIZE);
    assert(j < Board::SIZE);

    Block::Ptr block_p;

    Map::const_iterator pos = d_map.find(Coordinates(i, j));

    if(d_map.end() != pos)
    {
        block_p = pos->second;
    }

    return block_p;
}

} // Close goblb
