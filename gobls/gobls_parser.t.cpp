// gobls_parser.t.cpp

#include <gobls_parser.h>
#include <goblu_exception.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(Parser, parseValueAndBracket)
{
    {
        const char input[] = "";
        Lexer lexer(input);
        Parser::Data data;
        EXPECT_THROW(Parser::parseValueAndBracket(data, lexer), goblu::Exception);
    }
    {
        const char input[] = "]";
        Lexer lexer(input);
        Parser::Data data;
        EXPECT_THROW(Parser::parseValueAndBracket(data, lexer), goblu::Exception);
    }
    {
        const char input[] = "poop";
        Lexer lexer(input);
        Parser::Data data;
        EXPECT_THROW(Parser::parseValueAndBracket(data, lexer), goblu::Exception);
    }
    {
        //                    012345
        const char input[] = "hello]";
        Lexer lexer(input);
        Parser::Data data;
        EXPECT_NO_THROW(Parser::parseValueAndBracket(data, lexer));
        EXPECT_EQ(1u, data.size());
        EXPECT_EQ(TokenType::ID, data.begin()->type());
        EXPECT_EQ(input, data.begin()->begin());
        EXPECT_EQ(input + 5, data.begin()->end());
    }
}

} // Close gobls
