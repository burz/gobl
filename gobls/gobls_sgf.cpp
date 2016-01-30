// gobls_sgf.cpp

#include <gobls_sgf.h>

namespace gobls {

Sgf::Move Sgf::makePass()
{
    static constexpr unsigned int size = goblb::Board::SIZE;

    return Move(size, size);
}

} // Close gobls
