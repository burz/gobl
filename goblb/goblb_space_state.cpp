// goblb_space_state.cpp

#include <goblb_space_state.h>

namespace goblb {

const char* SpaceState::toString(const SpaceState::Value& state)
{
    switch(state)
    {
    case SpaceState::EMPTY:
        return "EMPTY";
    case SpaceState::BLACK:
        return "BLACK";
    case SpaceState::WHITE:
        return "WHITE";
    }
}


std::ostream& operator<<(std::ostream& stream, const SpaceState::Value& state)
{
    stream << SpaceState::toString(state);
    return stream;
}

} // Close goblb
