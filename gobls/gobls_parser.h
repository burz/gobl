// gobls_parser.h
#ifndef INCLUDED_GOBLS_PARSER
#define INCLUDED_GOBLS_PARSER

#ifndef INCLUDED_GOBLS_SGF
#include <gobls_sgf.h>
#endif

#include <string>

namespace gobls {

class Parser
{
  public:
    // CLASS METHODS
    static Sgf::Ptr parse(const std::string& file);
};

} // Close gobls

#endif
