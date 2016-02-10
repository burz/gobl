// gobls_lexer.h
#ifndef INCLUDED_GOBLS_LEXER
#define INCLUDED_GOBLS_LEXER

#ifndef INCLUDED_GOBLS_TOKEN
#include <gobls_token.h>
#endif

namespace gobls {

class Lexer
{
  public:
    // CLASS METHODS
    static const char* skipWhitespace(const char* input);
    static const char* skipParentheses(const char* input);

  private:
    const char* d_input;
    const char* d_idStart;

  public:
    // CREATORS
    Lexer(const char* input);

  public:
    // MANIPULATORS
    Token next();
    Token tryNext();
    void expect(TokenType::Value type);
};

} // Close gobls

#endif
