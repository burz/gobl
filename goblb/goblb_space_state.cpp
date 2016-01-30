// goblb_space_state.cpp

#include <goblb_space_state.h>

#include <sstream>

namespace goblb {

namespace {

constexpr char RESET[]  = "\e[0m";
constexpr char YELLOW[] = "\e[33m";
constexpr char BLUE[]   = "\e[34m";

} // Close anonymous

std::string SpaceState::toString(Value state, bool colors)
{
    std::ostringstream stream;

    switch(state)
    {
    case SpaceState::EMPTY:
        stream << "EMPTY";
        break;
    case SpaceState::BLACK:
        if(colors)
        {
            stream << BLUE;
        }
        stream << "BLACK";
        if(colors)
        {
            stream << RESET;
        }
        break;
    case SpaceState::WHITE:
        if(colors)
        {
            stream << YELLOW;
        }
        stream << "WHITE";
        if(colors)
        {
            stream << RESET;
        }
        break;
    }

    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, SpaceState::Value state)
{
    stream << SpaceState::toString(state, true);
    return stream;
}

} // Close goblb
