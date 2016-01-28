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
    // ACCESSORS
    const Space::Ptr& space(unsigned int i, unsigned int j) const;
};

inline
const Space::Ptr& Board::space(unsigned int i, unsigned int j) const
{
    assert(i < BOARD_SIZE);
    assert(j < BOARD_SIZE);

    return d_spaces[i][j];
}

} // Close goblb

#endif
