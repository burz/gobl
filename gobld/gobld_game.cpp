// gobld_game.cpp

#include <gobld_game.h>

namespace gobld {

Game::Game(gobls::Sgf::Ptr sgf_p)
: d_sgf_p(sgf_p)
{
    assert(sgf_p);

    d_iterator = sgf_p->begin();
    d_end      = sgf_p->end();
}

bool Game::next()
{
    if(d_end == d_iterator)
    {
        return false;
    }

    d_board.play(d_iterator->first, d_iterator->second);

    ++d_iterator;

    return true;
}

std::ostream& operator<<(std::ostream& stream, const Game& game)
{
    game.print(stream);

    return stream;
}

} // Close gobld
