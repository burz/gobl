// gobls_parser.h
#ifndef INCLUDED_GOBLS_PARSER
#define INCLUDED_GOBLS_PARSER

#ifndef INCLUDED_GOBLS_SGF
#include <gobls_sgf.h>
#endif

#ifndef INCLUDED_GOBLS_LEXER
#include <gobls_lexer.h>
#endif

#include <string>
#include <vector>

namespace gobls {

class Parser
{
  public:
    // TYPES
    typedef std::vector<Token>           Data;
    typedef std::pair<std::string, Data> DataPoint;
    typedef std::map<std::string, Data>  DataPoints;

  public:
    // CLASS METHODS
    static void parseValueAndBracket(Data& data, Lexer& lexer);
    static bool parseDataPoint(DataPoint& dataPoint, Lexer& lexer);
    static DataPoints parseDataPoints(Lexer& lexer);

    static Sgf::Ptr parseGame(Lexer& lexer);

    static Sgf::Ptr parseFile(const std::string& fileName);
};

} // Close gobls

#endif
