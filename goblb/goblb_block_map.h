// goblb_block_map.h
#ifndef INCLUDED_GOBLB_BLOCK_MAP
#define INCLUDED_GOBLB_BLOCK_MAP

#ifndef INCLUDED_GOBLB_BLOCK
#include <goblb_block.h>
#endif

#include <map>

namespace goblb {

class BlockMap
{
  public:
    // TYPES
    typedef std::pair<unsigned int, unsigned int> Coordinates;
    typedef std::map<Coordinates, Block::Ptr>      Map;

  private:
    // DATA
    Map d_map;

  public:
    // MANIPULATORS
    void insert(unsigned int i, unsigned int j, const Block::Ptr& block);
    void remove(unsigned int i, unsigned int j);

  public:
    // ACCESSORS
    Block::Ptr lookup(unsigned int i, unsigned int j) const;
};

} // Close goblb

#endif
