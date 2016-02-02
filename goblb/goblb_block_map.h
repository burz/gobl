// goblb_block_map.h
#ifndef INCLUDED_GOBLB_BLOCK_MAP
#define INCLUDED_GOBLB_BLOCK_MAP

#ifndef INCLUDED_GOBLB_BLOCK
#include <goblb_block.h>
#endif

#ifndef INCLUDED_GOBLB_SPACE
#include <goblb_space.h>
#endif

#include <iostream>
#include <map>

namespace goblb {

class BlockMap
{
  public:
    // TYPES
    typedef std::pair<unsigned int, unsigned int> Coordinates;
    typedef std::map<Coordinates, Block::Ptr>     Map;

  private:
    // DATA
    Map d_map;

  private:
    // PRIVATE MANIPULATORS
    void resetSpace(const Space::Ptr& space_p);

  public:
    // MANIPULATORS
    void insert(const Block::Ptr& block_p);
    void remove(const Block::Ptr& block_p);

  public:
    // ACCESSORS
    Block::Ptr lookup(unsigned int i, unsigned int j) const;
    Block::Ptr lookup(const Space::Ptr& space_p) const;

    void print(std::ostream& stream) const;
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const BlockMap& blockMap);

// INLINES
inline
Block::Ptr BlockMap::lookup(const Space::Ptr& space_p) const
{
    return lookup(space_p->i(), space_p->j());
}

} // Close goblb

#endif
