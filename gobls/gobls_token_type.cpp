// gobls_token_type.cpp

#include <gobls_token_type.h>

namespace gobls {

const char* TokenType::toString(Value type)
{
    switch(type)
    {
    case END:
        return "END";
    case LPARENS:
        return "LPARENS";
    case RPARENS:
        return "RPARENS";
    case ID:
        return "ID";
    case RBRACKET:
        return "RBRACKET";
    case LBRACKET:
        return "LBRACKET";
    };
}

std::ostream& operator<<(std::ostream& stream, TokenType::Value type)
{
    stream << TokenType::toString(type);

    return stream;
}

} // Close gobls
