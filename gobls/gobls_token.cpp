// gobls_token.cpp

#include <gobls_token.h>

namespace gobls {

Token::Token(
      TokenType::Value type
    , const char* begin
    , const char* end
)
: d_type(type)
, d_begin(begin)
, d_end(end)
{
}

} // Close gobls
