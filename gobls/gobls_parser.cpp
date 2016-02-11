// gobls_parser.cpp

#include <gobls_parser.h>
#include <goblu_exception.h>

namespace gobls {

namespace {

inline
unsigned int moveFromChar(char move)
{
    return static_cast<unsigned int>(move) - 97;
}

} // Close anonymous

void Parser::parseValueAndBracket(Data& data, Lexer& lexer)
{
    Token value = lexer.next();

    if(TokenType::RBRACKET == value.type()
    || TokenType::END      == value.type())
    {
        THROW_GOBL("Expected a value between the brackets.");
    }

    Token max;
    Token token = lexer.tryNext();

    while(TokenType::RBRACKET != token.type())
    {
        if(TokenType::END == token.type())
        {
            THROW_GOBL("Expected a closing ']' after the '['");
        }

        max = token;

        lexer.advance();

        token = lexer.tryNext();
    }

    if(TokenType::END != max.type())
    {
        data.push_back(Token(TokenType::ID, value.begin(), max.end()));
    }
    else
    {
        data.push_back(value);
    }

    lexer.advance();
}

bool Parser::parseDataPoint(Parser::DataPoint& dataPoint, Lexer& lexer)
{
    Token name = lexer.tryNext();

    if(TokenType::ID != name.type())
    {
        return false;
    }

    dataPoint.first = std::string(name.begin(), name.end());

    lexer.advance();
    lexer.expect(TokenType::LBRACKET);

    parseValueAndBracket(dataPoint.second, lexer);

    while(TokenType::LBRACKET == lexer.tryNext().type())
    {
        lexer.advance();

        parseValueAndBracket(dataPoint.second, lexer);
    }

    return true;
}

Parser::DataPoints Parser::parseDataPoints(Lexer& lexer)
{
    DataPoints results;

    while(true)
    {
        DataPoint dataPoint;

        if(!parseDataPoint(dataPoint, lexer))
        {
            break;
        }

        results.insert(dataPoint);
    }

    return results;
}

Sgf::Ptr Parser::parseGame(Lexer& lexer)
{
    Sgf::Ptr sgf_p(new Sgf());

    lexer.expect(TokenType::LPARENS);
    lexer.expect(TokenType::SEMI);

    DataPoints metadata = parseDataPoints(lexer);

    for(auto itt = metadata.begin(); itt != metadata.end(); ++itt)
    {
        const Token& token = itt->second[0];

        sgf_p->add(itt->first, std::string(token.begin(), token.end()));
    }

    while(TokenType::SEMI == lexer.tryNext().type())
    {
        lexer.advance();

        DataPoints dataPoints = parseDataPoints(lexer);

        DataPoints::const_iterator pos = dataPoints.find("B");

        if(dataPoints.end() == pos)
        {
            pos = dataPoints.find("W");
        }

        if(dataPoints.end() == pos)
        {
            THROW_GOBL("Couldn't parse a move (either 'B' or 'W').");
        }

        const char* chars = pos->second[0].begin();

        sgf_p->add(moveFromChar(chars[0]), moveFromChar(chars[1]));
    }

    lexer.expect(TokenType::RPARENS);

    return sgf_p;
}

} // Close gobls
