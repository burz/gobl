// gobls_sgf_iterator.cpp

#include <gobls_sgf_iterator.h>
#include <gobls_parser.h>

#include <cassert>
#include <stdexcept>

namespace gobls {

SgfIterator::SgfIterator(const Strings& strings, bool files)
: d_files(files)
, d_iterator(strings.begin())
, d_end(strings.end())
{
}

bool SgfIterator::next()
{
    return d_end == d_iterator;
}

Sgf::Ptr SgfIterator::value()
{
    assert(d_end != d_iterator);

    Sgf::Ptr result;

    try
    {
        Sgf::Ptr result;

        if(d_files)
        {
            result = Parser::parseFile(*d_iterator);
        }
        else
        {
            result = Parser::parseString(*d_iterator);
        }

        ++d_succeeded;
    }
    catch(const std::exception& exception)
    {
        std::cerr << "Caught exception while parsing the ";

        if(d_files)
        {
            std::cerr << "file \"";
        }
        else
        {
            std::cerr << "string \"";
        }

        std::cerr << *d_iterator << '"' << std::endl
                  << "With message \"" << exception.what()
                  << '"' << std::endl;

        ++d_failed;
    }

    return result;
}

} // Close gobls
