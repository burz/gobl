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

void Board::print(std::ostream& stream) const
{
    for(unsigned int i = 1; i <= BOARD_SIZE; i++)
    {
        const unsigned int k = BOARD_SIZE - i;

        stream << "[ " << *d_spaces[k][0];

        for(unsigned int j = 1; j < BOARD_SIZE; ++j)
        {
            stream << ", " << *d_spaces[k][j];
        }

        stream << " ]\n";
    }
}

bool Board::operator==(const Board& board)
{
    for(unsigned int i = 0; i < BOARD_SIZE; ++i)
    {
        for(unsigned int j = 0; j < BOARD_SIZE; ++j)
        {
            if(*d_spaces[i][j] != *board.d_spaces[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& stream, const Board& board)
{
    board.print(stream);

    return stream;
}

} // Close goblb
