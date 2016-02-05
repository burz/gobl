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
    unsigned int libs() const;
    SpaceState::Value state() const;

    const std::set<Space::Ptr>& members() const;
    const std::set<Space::Ptr>& liberties() const;

    void print(std::ostream& stream) const;

  public:
    // OPERATORS
    bool operator==(const Block& space) const;
    bool operator!=(const Block& space) const;
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const Block& block);

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
unsigned int Block::libs() const
{
    return d_liberties.size();
}

inline
SpaceState::Value Block::state() const
{
    assert(!d_members.empty());

    return (*d_members.begin())->state();
}

inline
const std::set<Space::Ptr>& Block::members() const
{
    return d_members;
}

inline
const std::set<Space::Ptr>& Block::liberties() const
{
    return d_liberties;
}

inline
bool Block::operator==(const Block& space) const
{
    return d_members == space.members()
        && d_liberties == space.liberties();
}

inline
bool Block::operator!=(const Block& space) const
{
    return !(*this == space);
}

} // Close goblb

#endif
