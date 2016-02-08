// gobls_sgf.h
#ifndef INCLUDED_GOBLS_SGF
#define INCLUDED_GOBLS_SGF

#ifndef INCLUDED_GOBLB_BOARD
#include <goblb_board.h>
#endif

#include <memory>
#include <vector>

namespace gobls {

class Sgf
{
  public:
    // TYPES
    typedef std::pair<unsigned int, unsigned int> Move;
    typedef std::shared_ptr<Sgf>                  Ptr;

  public:
    // CLASS METHODS
    static bool isPass(const Move& move);
    static Move makePass();

  private:
    // DATA
    std::vector<Move> d_moves;

  public:
    // MANIPULATORS
    void add(unsigned int i, unsigned int j);
};

// INLINES
inline
bool Sgf::isPass(const Move& move)
{
    return (goblb::Board::SIZE == move.first)
        && (goblb::Board::SIZE == move.second);
}

inline
void Sgf::add(unsigned int i, unsigned int j)
{
    d_moves.push_back(Move(i, j));
}

} // Close gobls

#endif
