// goblb_block.cpp

#include <goblb_block.h>

namespace goblb {

void Block::absorb(const Block& block)
{
    std::set<Space::Ptr>::const_iterator itt;

    for(itt = block.d_members.begin(); itt != block.d_members.end(); ++itt)
    {
        d_members.insert(*itt);
    }

    for(itt = block.d_liberties.begin(); itt != block.d_liberties.end(); ++itt)
    {
        d_liberties.insert(*itt);
    }
}

} // Close goblb
