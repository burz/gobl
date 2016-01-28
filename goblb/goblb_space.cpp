// goblb_space.cpp

#include <goblb_space.h>

namespace goblb {

Space::Space()
: d_state(SpaceState::EMPTY)
{
}

Space::Space(SpaceState::Value state)
: d_state(state)
{
}

} // Close goblb
