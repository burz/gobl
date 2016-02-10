// gobls_token.t.cpp

#include <gobls_token.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(Token, constructor)
{
    {
        Token token;
        EXPECT_EQ(TokenType::END, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        Token token(TokenType::LBRACKET);
        EXPECT_EQ(TokenType::LBRACKET, token.type());
        EXPECT_EQ(static_cast<const char*>(0), token.begin());
        EXPECT_EQ(static_cast<const char*>(0), token.end());
    }
    {
        const char input[] = "Hello, world!";
        Token token(TokenType::LBRACKET, input, input + sizeof(input));
        EXPECT_EQ(TokenType::LBRACKET, token.type());
        EXPECT_EQ(input, token.begin());
        EXPECT_EQ(input + sizeof(input), token.end());
    }
}

} // Close gobls
