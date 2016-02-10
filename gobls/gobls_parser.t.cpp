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

TEST(Parser, parseDataPoint)
{
    {
        const char input[] = "";
        Lexer lexer(input);
        Parser::DataPoint dataPoint;
        bool success = true;
        ASSERT_NO_THROW(success = Parser::parseDataPoint(dataPoint, lexer));
        EXPECT_FALSE(success);
    }
    {
        const char input[] = "hello";
        Lexer lexer(input);
        Parser::DataPoint dataPoint;
        EXPECT_THROW(Parser::parseDataPoint(dataPoint, lexer), goblu::Exception);
    }
    {
        const char input[] = "hello[oops";
        Lexer lexer(input);
        Parser::DataPoint dataPoint;
        EXPECT_THROW(Parser::parseDataPoint(dataPoint, lexer), goblu::Exception);
    }
    {
        const char input[] = "hello[";
        Lexer lexer(input);
        Parser::DataPoint dataPoint;
        EXPECT_THROW(Parser::parseDataPoint(dataPoint, lexer), goblu::Exception);
    }
    {
        //                    0123456789012
        const char input[] = "hello[world!]";
        Lexer lexer(input);
        Parser::DataPoint dataPoint;
        bool success = false;
        ASSERT_NO_THROW(success = Parser::parseDataPoint(dataPoint, lexer));
        EXPECT_TRUE(success);
        EXPECT_EQ(std::string(input, input + 5), dataPoint.first);
        ASSERT_EQ(1u, dataPoint.second.size());
        const Token& token = *dataPoint.second.begin();
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 6, token.begin());
        EXPECT_EQ(input + 12, token.end());
    }
    {
        //                    0123456789012345678901
        const char input[] = "TW[0.5][1.5][B][WHITE]";
        Lexer lexer(input);
        Parser::DataPoint dataPoint;
        bool success = false;
        ASSERT_NO_THROW(success = Parser::parseDataPoint(dataPoint, lexer));
        EXPECT_TRUE(success);
        EXPECT_EQ(std::string(input, input + 2), dataPoint.first);
        ASSERT_EQ(4u, dataPoint.second.size());
        Token token = dataPoint.second[0];
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 3, token.begin());
        EXPECT_EQ(input + 6, token.end());
        token = dataPoint.second[1];
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 8, token.begin());
        EXPECT_EQ(input + 11, token.end());
        token = dataPoint.second[2];
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 13, token.begin());
        EXPECT_EQ(input + 14, token.end());
        token = dataPoint.second[3];
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 16, token.begin());
        EXPECT_EQ(input + 21, token.end());
    }
}

} // Close gobls
