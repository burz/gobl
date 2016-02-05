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

void Block::print(std::ostream& stream) const
{
    stream << "<<";

    std::set<Space::Ptr>::const_iterator itt;

    for(itt = d_members.begin(); itt != d_members.end(); ++itt)
    {
        stream << '(' << (*itt)->i() << ", " << (*itt)->j() << ')';
    }

    stream << ">, <";

    for(itt = d_liberties.begin(); itt != d_liberties.end(); ++itt)
    {
        stream << '(' << (*itt)->i() << ", " << (*itt)->j() << ')';
    }

    stream << ">>";
}

std::ostream& operator<<(std::ostream& stream, const Block& block)
{
    block.print(stream);

    return stream;
}

} // Close goblb
