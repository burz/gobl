// goblb_board.cpp

#include <goblb_board.h>

namespace goblb {

void Board::handleAdjacentSpace(
      std::set<Block::Ptr>& adjacentFriends
    , std::vector<Space::Ptr>& newLiberties
    , Space::Ptr& potentialKo_p
    , unsigned int i
    , unsigned int j
    , const Space::Ptr& space_p
)
{
    if(SIZE <= i || SIZE <= j)
    {
        return;
    }

    const Space::Ptr& adjacent_p = space(i, j);

    if(SpaceState::EMPTY == adjacent_p->state())
    {
        newLiberties.push_back(adjacent_p);

        return;
    }

    const Block::Ptr& block_p = d_blockMap.lookup(i, j);

    if(space_p->state() == adjacent_p->state())
    {
        adjacentFriends.insert(block_p);

        return;
    }

    if(1 == block_p->libs())
    {
        d_score += (SpaceState::WHITE == space_p->state() ? -1 : 1)
                 * block_p->size();

        if(1 == block_p->size())
        {
            potentialKo_p = adjacent_p;
        }

        d_blockMap.remove(block_p);

        newLiberties.push_back(adjacent_p);
    }
    else
    {
        block_p->removeLiberty(space_p);
    }
}

void Board::linkAdjacentFriendsWith(
      std::set<Block::Ptr>& adjacentFriends
    , std::vector<Space::Ptr>& newLiberties
    , const Space::Ptr& space_p
)
{
    Block::Ptr block_p(new Block());

    block_p->addMember(space_p);

    for(auto itt = adjacentFriends.begin(); itt != adjacentFriends.end(); ++itt)
    {
        block_p->absorb(**itt);
    }

    d_blockMap.insert(block_p);

    for(auto itt = newLiberties.begin(); itt != newLiberties.end(); ++itt)
    {
        block_p->addLiberty(*itt);
    }
}

Board::Board()
: d_spaces(SIZE, std::vector<Space::Ptr>(SIZE))
, d_score(0)
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

    std::set<Block::Ptr> adjacentFriends;
    std::vector<Space::Ptr> newLiberties;
    Space::Ptr potentialKo_p;

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , potentialKo_p
        , i + 1
        , j
        , space_p
    );

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , potentialKo_p
        , i - 1
        , j
        , space_p
    );

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , potentialKo_p
        , i
        , j + 1
        , space_p
    );

    handleAdjacentSpace(
          adjacentFriends
        , newLiberties
        , potentialKo_p
        , i
        , j - 1
        , space_p
    );

    space_p->setState(value);

    linkAdjacentFriendsWith(adjacentFriends, newLiberties, space_p);

    Block::Ptr block_p = d_blockMap.lookup(space_p);

    assert(static_cast<bool>(block_p));

    if(1 == block_p->libs())
    {
        d_ko_p = potentialKo_p;
    }
    else
    {
        d_ko_p.reset();
    }
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
