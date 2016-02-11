// gobls_parser.cpp

#include <gobls_parser.h>
#include <goblu_exception.h>

namespace gobls {

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

    return sgf_p;
}

} // Close gobls
