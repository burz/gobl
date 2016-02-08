// gobls_lexer.cpp

#include <gobls_lexer.h>
#include <goblu_exception.h>

#include <cassert>

namespace gobls {

const char* Lexer::skipParentheses(const char* input)
{
    if('(' != *input)
        return input;

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

} // Close gobls
