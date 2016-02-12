// gobld_game_iterator.h
#ifndef INCLUDED_GOBLD_GAME_ITERATOR
#define INCLUDED_GOBLD_GAME_ITERATOR

#ifndef INCLUDED_GOBLD_GAME
#include <gobld_game.h>
#endif

#ifndef INCLUDED_GOBLS_SGF_ITERATOR
#include <gobls_sgf_iterator.h>
#endif

namespace gobld {

class GameIterator
{
  public:
    // TYPES
    typedef gobls::SgfIterator::Strings Strings;

  private:
    // DATA
    gobls::SgfIterator d_iterator;

  public:
    // CREATORS
    GameIterator(const Strings& strings, bool files = false);

  public:
    // MANIPULATORS
    bool next();

  public:
    // ACCESSORS
    Game value() const;
    unsigned int succeeded() const;
    unsigned int failed() const;
};

// INLINES
inline
bool GameIterator::next()
{
    return d_iterator.next();
}

inline
Game GameIterator::value() const
{
    return Game(d_iterator.value());
}

inline
unsigned int GameIterator::succeeded() const
{
    return d_iterator.succeeded();
}

inline
unsigned int GameIterator::failed() const
{
    return d_iterator.failed();
}

} // Close gobld

#endif
