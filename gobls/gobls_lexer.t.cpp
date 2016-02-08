// gobls_lexer.t.cpp

#include <gobls_lexer.h>
#include <goblu_exception.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(Lexer, skipParentheses)
{
    {
        const char input[] = "";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(input, pos);
    }
    {
        const char input[] = "Hello, world!";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(input, pos);
    }
    {
        const char input[] = "(ello";
        const char* pos;
        EXPECT_THROW(pos = Lexer::skipParentheses(input), goblu::Exception);
    }
    {
        const char input[] = "()";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(input + sizeof(input) - 1, pos);
    }
    {
        const char input[] = "( hello, WORLD!!)";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(input + sizeof(input) - 1, pos);
    }
    {
        const char input[] = "(()()()()(()())(((()()))))";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(input + sizeof(input) - 1, pos);
    }
}

} // Close gobls
