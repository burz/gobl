// gobls_token.h
#ifndef INCLUDED_GOBLS_TOKEN
#define INCLUDED_GOBLS_TOKEN

#ifndef INCLUDED_GOBLS_TOKEN_TYPE
#include <gobls_token_type.h>
#endif

namespace gobls {

class Token
{
  private:
    // DATA
    TokenType::Value d_type;
    const char*      d_begin;
    const char*      d_end;

  public:
    // CREATORS
    Token(
          TokenType::Value type = TokenType::END
        , const char* begin = 0
        , const char* end = 0
    );

  public:
    // ACCESSORS
    TokenType::Value type() const;
    const char* begin() const;
    const char* end() const;
};

inline
TokenType::Value Token::type() const
{
    return d_type;
}

inline
const char* Token::begin() const
{
    return d_begin;
}

inline
const char* Token::end() const
{
    return d_end;
}

} // Close gobls

#endif
