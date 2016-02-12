// gobld_game_iterator.cpp

#include <gobld_game_iterator.h>

namespace gobld {

GameIterator::GameIterator(const Strings& strings, bool files)
: d_iterator(strings, files)
{
}

} // Close gobld
