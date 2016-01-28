// goblb_space_state.h
#ifndef INCLUDED_GOBLB_SPACE_STATE
#define INCLUDED_GOBLB_SPACE_STATE

#include <iostream>

namespace goblb {

class SpaceState
{
  public:
    // TYPES
    enum Value
    {
          EMPTY = 0
        , BLACK = 1
        , WHITE = 2
    };

  public:
    // CLASS METHODS
    static const char* toString(Value state);
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, SpaceState::Value state);

} // Close goblb

#endif
