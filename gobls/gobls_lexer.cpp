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
, d_idStart(0)
{
}

#define GOBLS_RETURN_NEXT_TYPE(gobls__type)              \
    if(d_idStart)                                        \
    {                                                    \
        Token result(TokenType::ID, d_idStart, d_input); \
        d_idStart = 0;                                   \
        return result;                                   \
    }                                                    \
    else                                                 \
    {                                                    \
        Token result(gobls__type);                       \
        ++d_input;                                       \
        return result;                                   \
    }

Token Lexer::next()
{
    if(0 == d_input)
    {
        GOBLS_RETURN_NEXT_TYPE(TokenType::END);
    }

    d_input = skipWhitespace(d_input);

    switch(*d_input)
    {
    case '(':
        GOBLS_RETURN_NEXT_TYPE(TokenType::LPARENS);
        break;
    case ')':
        GOBLS_RETURN_NEXT_TYPE(TokenType::RPARENS);
        break;
    case '[':
        GOBLS_RETURN_NEXT_TYPE(TokenType::LBRACKET);
        break;
    case ']':
        GOBLS_RETURN_NEXT_TYPE(TokenType::RBRACKET);
        break;
    default:
        break;
    }

    if(0 == d_idStart)
    {
        d_idStart = d_input;
    }

    ++d_input;

    return next();
}

Token Lexer::tryNext()
{
    const char* start = d_input;

    Token result = next();

    d_input = start;

    return result;
}

} // Close gobls
