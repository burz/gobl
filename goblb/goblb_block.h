// goblb_block.h
#ifndef INCLUDED_GOBLB_BLOCK
#define INCLUDED_GOBLB_BLOCK

#ifndef INCLUDED_GOBLB_SPACE
#include <goblb_space.h>
#endif

#ifndef INCLUDED_GOBLB_SPACE_STATE
#include <goblb_space_state.h>
#endif

#include <cassert>
#include <memory>
#include <set>

namespace goblb {

class Block
{
  public:
    // TYPES
    typedef std::shared_ptr<Block> Ptr;

  private:
    // DATA
    std::set<Space::Ptr> d_members;
    std::set<Space::Ptr> d_liberties;

  public:
    // MANIPULATORS
    void addMember(const Space::Ptr& space);
    void addLiberty(const Space::Ptr& space);
    void removeLiberty(const Space::Ptr& space);

    void absorb(const Block& block);

  public:
    // ACCESSORS
    unsigned int size() const;
    unsigned int liberties() const;
};

// INLINES
inline
void Block::addMember(const Space::Ptr& space)
{
    assert(SpaceState::EMPTY != space->state());
    assert(d_members.empty() || (*d_members.begin())->state() == space->state());

    d_members.insert(space);
}

inline
void Block::addLiberty(const Space::Ptr& space)
{
    assert(SpaceState::EMPTY == space->state());

    d_liberties.insert(space);
}

inline
void Block::removeLiberty(const Space::Ptr& space)
{
    assert(d_liberties.end() != d_liberties.find(space));

    d_liberties.erase(space);
}

inline
unsigned int Block::size() const
{
    return d_members.size();
}

inline
unsigned int Block::liberties() const
{
    return d_liberties.size();
}

} // Close goblb

#endif
