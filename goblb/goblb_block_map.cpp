// goblb_block_map.cpp

#include <goblb_block_map.h>
#include <goblb_board.h>

#include <cassert>

namespace goblb {

void BlockMap::insert(unsigned int i, unsigned int j, const Block::Ptr& block)
{
    assert(i < Board::SIZE);
    assert(j < Board::SIZE);

    Coordinates coordinates(i, j);

    assert(d_map.end() == d_map.find(coordinates));

    d_map.insert(Map::value_type(coordinates, block));
}

void BlockMap::remove(unsigned int i, unsigned int j)
{
    assert(i < Board::SIZE);
    assert(j < Board::SIZE);

    Coordinates coordinates(i, j);

    assert(d_map.end() != d_map.find(coordinates));

    d_map.erase(coordinates);
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
