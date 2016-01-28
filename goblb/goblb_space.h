// goblb_space.h
#ifndef INCLUDED_GOBLB_SPACE
#define INCLUDED_GOBLB_SPACE

#ifndef INCLUDED_GOBLB_SPACE_STATE
#include <goblb_space_state.h>
#endif

namespace goblb {

class Space
{
  private:
    // DATA
    SpaceState::Value d_state;

  public:
    // CREATORS
    Space();
    Space(SpaceState::Value state);

  public:
    // ACCESSORS
    SpaceState::Value state() const;
};

inline
SpaceState::Value Space::state() const
{
    return d_state;
}


} // Close goblb

#endif
