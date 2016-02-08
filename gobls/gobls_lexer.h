// gobls_lexer.h
#ifndef INCLUDED_GOBLS_LEXER
#define INCLUDED_GOBLS_LEXER

namespace gobls {

class Lexer
{
  public:
    // CLASS METHODS
    static const char* skipParentheses(const char* input);
};

} // Close gobls

#endif
