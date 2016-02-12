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
, d_succeeded(0)
, d_failed(0)
{
}

bool SgfIterator::next()
{
    d_next.reset();

    if(d_end == d_iterator)
    {
        return false;
    }

    try
    {
        if(d_files)
        {
            d_next = Parser::parseFile(*d_iterator);
        }
        else
        {
            d_next = Parser::parseString(*d_iterator);
        }

        ++d_succeeded;
        ++d_iterator;

        return true;
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
        ++d_iterator;

        return next();
    }
}

} // Close gobls
