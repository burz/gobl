// gobls_lexer.cpp

#include <gobls_lexer.h>
#include <goblu_exception.h>

#include <cassert>

namespace gobls {

const char* Lexer::skipWhitespace(const char* input)
{
    assert(input);

    while(true)
    {
        switch(*input)
        {
        case ' ':
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
            ++input;
            break;
        default:
            return input;
        }
    }
}

const char* Lexer::skipParentheses(const char* input)
{
    assert(input);

    if('(' != *input)
    {
        return input;
    }

    ++input;

    unsigned int level = 1;

    while(0 != level)
    {
        switch(*input)
        {
        case '(':
            ++level;
            break;
        case ')':
            --level;
            break;
        case 0:
            THROW_GOBL("Found unterminated parentheses.");
            break;
        default:
            break;
        }

        ++input;
    }

    return input;
}

Lexer::Lexer(const char* input)
: d_input(input)
, d_saved(0)
, d_idStart(0)
{
    assert(d_input);
}

#define GOBLS_NEXT_RETURN(gobls__type)                   \
    if(d_idStart)                                        \
    {                                                    \
        Token result(TokenType::ID, d_idStart, d_input); \
        d_idStart = 0;                                   \
        return result;                                   \
    }                                                    \
    else                                                 \
    {                                                    \
        Token result(gobls__type, d_input, d_input + 1); \
        ++d_input;                                       \
        return result;                                   \
    }

Token Lexer::next()
{
    const char* pos = skipWhitespace(d_input);

    if(d_input != pos)
    {
        if(0 != d_idStart)
        {
            Token result(TokenType::ID, d_idStart, d_input);

            d_idStart = 0;
            d_input   = pos;

            return result;
        }

        d_input = pos;
    }

    switch(*d_input)
    {
    case 0:
        GOBLS_NEXT_RETURN(TokenType::END);
        break;
    case '(':
        GOBLS_NEXT_RETURN(TokenType::LPARENS);
        break;
    case ')':
        GOBLS_NEXT_RETURN(TokenType::RPARENS);
        break;
    case '[':
        GOBLS_NEXT_RETURN(TokenType::LBRACKET);
        break;
    case ']':
        GOBLS_NEXT_RETURN(TokenType::RBRACKET);
        break;
    case ';':
        GOBLS_NEXT_RETURN(TokenType::SEMI);
        break;
    case '\\':
        if(0 == d_idStart)
        {
            d_idStart = d_input;
        }
        if(']' == *(d_input + 1))
        {
            ++d_input;
        }
        ++d_input;
        return next();
        break;
    default:
        if(0 == d_idStart)
        {
            d_idStart = d_input;
        }
        ++d_input;
        return next();
        break;
    }
}

Token Lexer::tryNext()
{
    const char* start = d_input;

    Token result = next();

    d_saved = d_input;
    d_input = start;

    return result;
}

void Lexer::expect(TokenType::Value type)
{
    Token result = next();

    if(type != result.type())
    {
        THROW_GOBL("Expected a '" << type << "'");
    }
}

} // Close gobls
