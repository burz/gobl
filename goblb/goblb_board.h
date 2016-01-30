// goblb_board.h
#ifndef INCLUDED_GOBLB_BOARD
#define INCLUDED_GOBLB_BOARD

#ifndef INCLUDED_GOBLB_BLOCK_MAP
#include <goblb_block_map.h>
#endif

#ifndef INCLUDED_GOBLB_SPACE
#include <goblb_space.h>
#endif

#include <cassert>
#include <set>
#include <vector>

namespace goblb {

class Board
{
  public:
    // CLASS DATA
    static constexpr unsigned int SIZE = 19;

  private:
    // DATA
    std::vector<std::vector<Space::Ptr> > d_spaces;
    BlockMap                              d_blockMap;
    int                                   d_score;
    Space::Ptr                            d_ko_p;

  private:
    // PRIVATE MANIPULATORS
    void handleAdjacentSpace(
          std::set<Block::Ptr>& adjacentFriends
        , std::vector<Space::Ptr>& newLiberties
        , Space::Ptr& potentialKo_p
        , unsigned int i
        , unsigned int j
        , const Space::Ptr& space_p
    );

    void linkAdjacentFriendsWith(
          std::set<Block::Ptr>& adjacentFriends
        , std::vector<Space::Ptr>& newLiberties
        , const Space::Ptr& space_p
    );

  public:
    // CREATORS
    Board();

  public:
    // MANIPULATORS
    void setState(unsigned int i, unsigned int j, SpaceState::Value value);
    void play(unsigned int i, unsigned int j, SpaceState::Value value);

  public:
    // ACCESSORS
    const Space::Ptr& space(unsigned int i, unsigned int j) const;
    SpaceState::Value state(unsigned int i, unsigned int j) const;
    const Space::Ptr& ko() const;

    void print(std::ostream& stream) const;

  public:
    // OPERATORS
    bool operator==(const Board& board);
    bool operator!=(const Board& board);
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const Board& board);

// INLINES
inline
void Board::setState(unsigned int i, unsigned int j, SpaceState::Value value)
{
    assert(i < SIZE);
    assert(j < SIZE);

    d_spaces[i][j]->setState(value);
}

inline
const Space::Ptr& Board::space(unsigned int i, unsigned int j) const
{
    assert(i < SIZE);
    assert(j < SIZE);

    return d_spaces[i][j];
}

inline
SpaceState::Value Board::state(unsigned int i, unsigned int j) const
{
    assert(i < SIZE);
    assert(j < SIZE);

    return d_spaces[i][j]->state();
}

inline
const Space::Ptr& Board::ko() const
{
    return d_ko_p;
}

inline
bool Board::operator!=(const Board& board)
{
    return !(*this == board);
}

} // Close goblb

#endif
