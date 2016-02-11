// gobls_parser.cpp

#include <gobls_parser.h>
#include <goblu_exception.h>

namespace gobls {

void Parser::parseValueAndBracket(Data& data, Lexer& lexer)
{
    Token value = lexer.tryNext();

    if(TokenType::ID != value.type())
    {
        THROW_GOBL("Expected a value between the brackets.");
    }

    Token max;
    for(Token token = lexer.tryNext()
      ; TokenType::ID == token.type()
      ; token = lexer.tryNext())
    {
        max = token;

        lexer.advance();
    }

    if(TokenType::ID == max.type())
    {
        data.push_back(Token(TokenType::ID, value.begin(), max.end()));
    }
    else
    {
        data.push_back(value);
    }

    lexer.expect(TokenType::RBRACKET);
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

} // Close gobls
