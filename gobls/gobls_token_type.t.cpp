// gobls_token_type.t.cpp

#include <gobls_token_type.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(TokenType, toString)
{
    EXPECT_STREQ("END", TokenType::toString(TokenType::END));
    EXPECT_STREQ("LPARENS", TokenType::toString(TokenType::LPARENS));
    EXPECT_STREQ("RPARENS", TokenType::toString(TokenType::RPARENS));
    EXPECT_STREQ("ID", TokenType::toString(TokenType::ID));
    EXPECT_STREQ("LBRACKET", TokenType::toString(TokenType::LBRACKET));
    EXPECT_STREQ("RBRACKET", TokenType::toString(TokenType::RBRACKET));
    EXPECT_STREQ("SEMI", TokenType::toString(TokenType::SEMI));
}

} // Close gobls
