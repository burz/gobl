// goblb_board.cpp

#include <goblb_board.h>

namespace goblb {

Board::Board()
: d_spaces(BOARD_SIZE, std::vector<Space::Ptr>(BOARD_SIZE))
{
    for(unsigned int i = 0; i < BOARD_SIZE; ++i)
    {
        for(unsigned int j = 0; j < BOARD_SIZE; ++j)
        {
            d_spaces[i][j].reset(new Space());
        }
    }
}

} // Close goblb
