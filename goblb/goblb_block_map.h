// goblb_block_map.h
#ifndef INCLUDED_GOBLB_BLOCK_MAP
#define INCLUDED_GOBLB_BLOCK_MAP

#ifndef INCLUDED_GOBLB_BLOCK
#include <goblb_block.h>
#endif

#ifndef INCLUDED_GOBLB_SPACE
#include <goblb_space.h>
#endif

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

  public:
    // MANIPULATORS
    void insert(const Block::Ptr& block);
    void remove(const Block::Ptr& block);

  public:
    // ACCESSORS
    Block::Ptr lookup(unsigned int i, unsigned int j) const;
    Block::Ptr lookup(const Space::Ptr& space_p) const;
};

// INLINES
inline
Block::Ptr BlockMap::lookup(const Space::Ptr& space_p) const
{
    return lookup(space_p->i(), space_p->j());
}

} // Close goblb

#endif
