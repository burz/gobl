// gobls_sgf.cpp

#include <gobls_sgf.h>
#include <goblu_exception.h>

namespace gobls {

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

} // Close gobls
