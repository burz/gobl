// gobls_lexer.t.cpp

#include <gobls_lexer.h>
#include <goblu_exception.h>

#include <gtest/gtest.h>

namespace gobls {

#define GOBLS_END(gobls__string) (gobls__string + sizeof(gobls__string) - 1)

TEST(Lexer, skipWhitespace)
{
    {
        const char input[] = "";
        EXPECT_EQ(input, Lexer::skipWhitespace(input));
    }
    {
        const char input[] = "q";
        EXPECT_EQ(input, Lexer::skipWhitespace(input));
    }
    {
        const char input[] = " \t\n\v\f\r";
        EXPECT_EQ(GOBLS_END(input), Lexer::skipWhitespace(input));
    }
    {
        const char input[] = " \f \t    \t   \v\v\r\v\v   \n \n\v  \f\r \n \r";
        EXPECT_EQ(GOBLS_END(input), Lexer::skipWhitespace(input));
    }
}

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
        EXPECT_EQ(GOBLS_END(input), pos);
    }
    {
        const char input[] = "( hello, WORLD!!)";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(GOBLS_END(input), pos);
    }
    {
        const char input[] = "(()()()()(()())(((()()))))";
        const char* pos = Lexer::skipParentheses(input);
        EXPECT_EQ(GOBLS_END(input), pos);
    }
}

TEST(Lexer, constructor)
{
    Lexer lexer("");
}

TEST(Lexer, next)
{
    {
        const char input[] = "";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = " \t\n\v\f";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = "(";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::LPARENS, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = ")";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::RPARENS, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = "[";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::LBRACKET, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = "]";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::RBRACKET, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = ";";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::SEMI, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = "hello";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input, token.begin());
        EXPECT_EQ(GOBLS_END(input), token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        //                    01 2 34567890
        const char input[] = "  \r\f hello \f\n  ";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 5, token.begin());
        EXPECT_EQ(input + 10, token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
    }
    {
        //                    0123 45 678901 2345678
        const char input[] = ";(]\f[)\rhello\t[mate]\n(); ;\v";
        Lexer lexer(input);
        Token token = lexer.next();
        EXPECT_EQ(TokenType::SEMI, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::LPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::RBRACKET, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::LBRACKET, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::RPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 7, token.begin());
        EXPECT_EQ(input + 12, token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::LBRACKET, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 14, token.begin());
        EXPECT_EQ(input + 18, token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::RBRACKET, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::LPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::RPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::SEMI, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::SEMI, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
    }
}

TEST(Lexer, tryNext)
{
    {
        const char input[] = "";
        Lexer lexer(input);
        Token token = lexer.tryNext();
        EXPECT_EQ(TokenType::END, token.type());
        token = lexer.tryNext();
        EXPECT_EQ(TokenType::END, token.type());
    }
    {
        //                    01 2 34567890
        const char input[] = "  \r\f hello \f\n() ";
        Lexer lexer(input);
        Token token = lexer.tryNext();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 5, token.begin());
        EXPECT_EQ(input + 10, token.end());
        token = lexer.next();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 5, token.begin());
        EXPECT_EQ(input + 10, token.end());
        token = lexer.tryNext();
        EXPECT_EQ(TokenType::LPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::LPARENS, token.type());
        token = lexer.tryNext();
        EXPECT_EQ(TokenType::RPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::RPARENS, token.type());
        token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
    }
}

TEST(Lexer, advance)
{
    const char input[] = "qq\n( ; ";
    Lexer lexer(input);
    Token token = lexer.tryNext();
    EXPECT_EQ(TokenType::ID, token.type());
    EXPECT_EQ(input + 0, token.begin());
    EXPECT_EQ(input + 2, token.end());
    lexer.advance();
    token = lexer.tryNext();
    EXPECT_EQ(TokenType::LPARENS, token.type());
    lexer.advance();
    token = lexer.tryNext();
    EXPECT_EQ(TokenType::SEMI, token.type());
    lexer.advance();
    token = lexer.tryNext();
    EXPECT_EQ(TokenType::END, token.type());
}

TEST(Lexer, expect)
{
    {
        const char input[] = "";
        Lexer lexer(input);
        EXPECT_THROW(lexer.expect(TokenType::SEMI), goblu::Exception);
    }
    {
        const char input[] = "()";
        Lexer lexer(input);
        EXPECT_THROW(lexer.expect(TokenType::SEMI), goblu::Exception);
    }
    {
        const char input[] = ";";
        Lexer lexer(input);
        EXPECT_NO_THROW(lexer.expect(TokenType::SEMI));
        Token token = lexer.next();
        EXPECT_EQ(TokenType::END, token.type());
    }
}

TEST(Lexer, allowsEscapedRBracket)
{
    //                    012 34567890 1234567
    const char input[] = "wow\\]that's\\]nice";
    Lexer lexer(input);
    Token token = lexer.next();
    EXPECT_EQ(TokenType::ID, token.type());
    EXPECT_EQ(input + 0, token.begin());
    EXPECT_EQ(input + 17, token.end());
}

} // Close gobls
