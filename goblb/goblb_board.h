// goblb_board.h
#ifndef INCLUDED_GOBLB_BOARD
#define INCLUDED_GOBLB_BOARD

#ifndef INCLUDED_GOBLB_SPACE
#include <goblb_space.h>
#endif

#include <cassert>
#include <vector>

namespace goblb {

class Board
{
  public:
    // CLASS DATA
    static constexpr unsigned int BOARD_SIZE = 19;

  private:
    // DATA
    std::vector<std::vector<Space::Ptr> > d_spaces;

  public:
    // CREATORS
    Board();

  public:
    // MANIPULATORS
    void setState(unsigned int i, unsigned int j, SpaceState::Value state);

  public:
    // ACCESSORS
    const Space::Ptr& space(unsigned int i, unsigned int j) const;
    SpaceState::Value state(unsigned int i, unsigned int j) const;

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
void Board::setState(unsigned int i, unsigned int j, SpaceState::Value state)
{
    assert(i < BOARD_SIZE);
    assert(j < BOARD_SIZE);

    d_spaces[i][j]->setState(state);
}

inline
const Space::Ptr& Board::space(unsigned int i, unsigned int j) const
{
    assert(i < BOARD_SIZE);
    assert(j < BOARD_SIZE);

    return d_spaces[i][j];
}

inline
SpaceState::Value Board::state(unsigned int i, unsigned int j) const
{
    assert(i < BOARD_SIZE);
    assert(j < BOARD_SIZE);

    return d_spaces[i][j]->state();
}

inline
bool Board::operator!=(const Board& board)
{
    return !(*this == board);
}

} // Close goblb

#endif
