// gobls_sgf.cpp

#include <gobls_sgf.h>
#include <goblu_exception.h>

namespace gobls {

namespace {

inline
char toChar(unsigned int i)
{
    return static_cast<char>(i + 97);
}

} // Close anonymous

Sgf::Move Sgf::makePass()
{
    static constexpr unsigned int size = goblb::Board::SIZE;

    return Move(size, size);
}

const std::string& Sgf::lookup(const std::string& attribute) const
{
    Metadata::const_iterator pos = d_metadata.find(attribute);

    if(d_metadata.end() == pos)
    {
        THROW_GOBL("Attribute '" << attribute << " not found.");
    }

    return pos->second;
}

void Sgf::print(std::ostream& stream) const
{
    stream << "(;" << std::endl;

    for(auto itt = d_metadata.begin(); itt != d_metadata.end(); ++itt)
    {
        stream << "  " << itt->first << '['
               << itt->second << ']' << std::endl;
    }

    goblb::SpaceState::Value turn = goblb::SpaceState::BLACK;

    for(auto itt = d_moves.begin(); itt != d_moves.end(); ++itt)
    {
        stream << "; "
               << (goblb::SpaceState::BLACK == turn ? "B[" : "W[")
               << toChar(itt->first) << toChar(itt->second)
               << ']' << std::endl;

        turn = goblb::SpaceState::BLACK == turn
            ? goblb::SpaceState::WHITE
            : goblb::SpaceState::BLACK;
    }

    stream << ')' << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Sgf& sgf)
{
    sgf.print(stream);

    return stream;
}

} // Close gobls
