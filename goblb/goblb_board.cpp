// goblb_board.cpp

#include <goblb_board.h>

namespace goblb {

void Board::handleAdjacentSpace(
      std::vector<Space::Ptr>& adjacentFriends
    , std::vector<Space::Ptr>& newLiberties
    , unsigned int i
    , unsigned int j
    , const Space::Ptr& space_p
)
{
}

void Board::linkAdjacentFriendsWith(
      std::vector<Space::Ptr>& adjacentFriends
    , std::vector<Space::Ptr>& newLiberties
    , const Space::Ptr& space_p
)
{
}

Board::Board()
: d_spaces(SIZE, std::vector<Space::Ptr>(SIZE))
{
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            d_spaces[i][j].reset(new Space(i, j));
        }
    }
}

void Board::play(unsigned int i, unsigned int j, SpaceState::Value value)
{
    assert(SpaceState::EMPTY == state(i, j));

    const Space::Ptr& space_p = d_spaces[i][j];

    space_p->setState(value);

    std::vector<Space::Ptr> adjacentFriends;
    std::vector<Space::Ptr> newLiberties;

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , i + 1
        , j
        , space_p
    );

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , i - 1
        , j
        , space_p
    );

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , i
        , j + 1
        , space_p
    );

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , i
        , j - 1
        , space_p
    );

    linkAdjacentFriendsWith(adjacentFriends, newLiberties, space_p);
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
