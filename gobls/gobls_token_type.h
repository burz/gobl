// gobls_token_type.h
#ifndef INCLUDED_GOBLS_TOKEN_TYPE
#define INCLUDED_GOBLS_TOKEN_TYPE

#include <iostream>

namespace gobls {

class TokenType
{
  public:
    // TYPES
    enum Value
    {
          END      = 0
        , LPARENS  = 1
        , RPARENS  = 2
        , ID       = 3
        , RBRACKET = 4
        , LBRACKET = 5
        , SEMI     = 6
    };

  public:
    // CLASS METHODS
    static const char* toString(Value type);

  private:
    // NOT IMPLEMENTED
    TokenType();
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const TokenType& type);

} // Close gobls

#endif
