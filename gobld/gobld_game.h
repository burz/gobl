// gobld_game.h
#ifndef INCLUDED_GOBLD_GAME
#define INCLUDED_GOBLD_GAME

#ifndef INCLUDED_GOBLB_BOARD
#include <goblb_board.h>
#endif

#ifndef INCLUDED_GOBLR_GENERATOR
#include <goblr_generator.h>
#endif

#ifndef INCLUDED_GOBLS_SGF
#include <gobls_sgf.h>
#endif

namespace gobld {

class Game
{
  private:
    // DATA
    gobls::Sgf::Ptr d_sgf_p;

    gobls::Sgf::Iterator d_iterator;
    gobls::Sgf::Iterator d_end;
    goblb::Board         d_board;

  public:
    // CREATORS
    Game(gobls::Sgf::Ptr sgf_p);

  public:
    // MANIPULATORS
    bool next();

  public:
    // ACCESSORS
    const std::string& metadata(const std::string& attribute) const;

    goblr::MatrixGroup::Ptr matrixGroup(
          goblb::SpaceState::Value perspective
        , unsigned int levels
    ) const;

    void print(std::ostream& stream) const;
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const Game& game);

// INLINES
inline
const std::string& Game::metadata(const std::string& attribute) const
{
    return d_sgf_p->lookup(attribute);
}

inline
goblr::MatrixGroup::Ptr Game::matrixGroup(
      goblb::SpaceState::Value perspective
    , unsigned int levels
) const
{
    return goblr::Generator::representation(
          d_board
        , perspective
        , levels
    );
}

inline
void Game::print(std::ostream& stream) const
{
    d_board.print(stream);
}

} // Close gobld

#endif
