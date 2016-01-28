// goblb_space.h
#ifndef INCLUDED_GOBLB_SPACE
#define INCLUDED_GOBLB_SPACE

#ifndef INCLUDED_GOBLB_SPACE_STATE
#include <goblb_space_state.h>
#endif

#include <memory>

namespace goblb {

class Space
{
  public:
    // TYPES
    typedef std::shared_ptr<Space> Ptr;

  private:
    // DATA
    SpaceState::Value d_state;

  public:
    // CREATORS
    Space();
    Space(SpaceState::Value state);

  public:
    // MANIPULATORS
    void setState(SpaceState::Value value);

  public:
    // ACCESSORS
    SpaceState::Value state() const;

    void print(std::ostream& stream) const;

  public:
    // OPERATORS
    bool operator==(const Space& space);
    bool operator!=(const Space& space);
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const Space& space);

// INLINES
inline
void Space::setState(SpaceState::Value value)
{
    d_state = value;
}

inline
SpaceState::Value Space::state() const
{
    return d_state;
}

inline
bool Space::operator==(const Space& space)
{
    return d_state == space.d_state;
}

inline
bool Space::operator!=(const Space& space)
{
    return d_state != space.d_state;
}

} // Close goblb

#endif
