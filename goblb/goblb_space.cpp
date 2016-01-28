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

void Space::print(std::ostream& stream) const
{
    stream << d_state;
}

std::ostream& operator<<(std::ostream& stream, const Space& space)
{
    space.print(stream);

    return stream;
}

} // Close goblb
