// goblb_board.cpp

#include <goblb_board.h>

namespace goblb {

Board::Board()
: d_spaces(SIZE, std::vector<Space::Ptr>(SIZE))
{
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            d_spaces[i][j].reset(new Space());
        }
    }
}

void Board::play(unsigned int i, unsigned int j, SpaceState::Value value)
{
    assert(SpaceState::EMPTY == state(i, j));
}

void Board::print(std::ostream& stream) const
{
    for(unsigned int i = 1; i <= SIZE; i++)
    {
        const unsigned int k = SIZE - i;

        stream << "[ " << *d_spaces[k][0];

        for(unsigned int j = 1; j < SIZE; ++j)
        {
            stream << ", " << *d_spaces[k][j];
        }

        stream << " ]\n";
    }
}

bool Board::operator==(const Board& board)
{
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
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
