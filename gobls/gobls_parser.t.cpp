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

TEST(Parser, parseDataPoints)
{
    {
        const char input[] = "";
        Lexer lexer(input);
        Parser::DataPoints dataPoints;
        ASSERT_NO_THROW(dataPoints = Parser::parseDataPoints(lexer));
        EXPECT_EQ(0u, dataPoints.size());
    }
    {
        //                    0123
        const char input[] = "A[U]";
        Lexer lexer(input);
        Parser::DataPoints dataPoints;
        ASSERT_NO_THROW(dataPoints = Parser::parseDataPoints(lexer));
        ASSERT_EQ(1u, dataPoints.size());
        const Parser::DataPoint& dataPoint = *dataPoints.begin();
        EXPECT_EQ(std::string(input, input + 1), dataPoint.first);
        ASSERT_EQ(1u, dataPoint.second.size());
        const Token& token = dataPoint.second[0];
        EXPECT_EQ(TokenType::ID, token.type());
        EXPECT_EQ(input + 2, token.begin());
        EXPECT_EQ(input + 3, token.end());
    }
    {
        const char input[] = "A[U]A[";
        Lexer lexer(input);
        Parser::DataPoints dataPoints;
        EXPECT_THROW(dataPoints = Parser::parseDataPoints(lexer), goblu::Exception);
    }
    {
        //                    0123456789012345 678901234567890123
        const char input[] = "  A[U]B[Ijksld] \nC[T][2] 2444[ksf]";
        Lexer lexer(input);
        Parser::DataPoints dataPoints;
        ASSERT_NO_THROW(dataPoints = Parser::parseDataPoints(lexer));
        ASSERT_EQ(4u, dataPoints.size());
        {
            Parser::DataPoints::const_iterator pos = dataPoints.find("A");
            ASSERT_NE(dataPoints.end(), pos);
            EXPECT_EQ(std::string(input + 2, input + 3), pos->first);
            ASSERT_EQ(1u, pos->second.size());
            const Token& token = pos->second[0];
            EXPECT_EQ(TokenType::ID, token.type());
            EXPECT_EQ(input + 4, token.begin());
            EXPECT_EQ(input + 5, token.end());
        }
        {
            Parser::DataPoints::const_iterator pos = dataPoints.find("B");
            ASSERT_NE(dataPoints.end(), pos);
            EXPECT_EQ(std::string(input + 6, input + 7), pos->first);
            ASSERT_EQ(1u, pos->second.size());
            const Token& token = pos->second[0];
            EXPECT_EQ(TokenType::ID, token.type());
            EXPECT_EQ(input + 8, token.begin());
            EXPECT_EQ(input + 14, token.end());
        }
        {
            Parser::DataPoints::const_iterator pos = dataPoints.find("C");
            ASSERT_NE(dataPoints.end(), pos);
            EXPECT_EQ(std::string(input + 17, input + 18), pos->first);
            ASSERT_EQ(2u, pos->second.size());
            Token token = pos->second[0];
            EXPECT_EQ(TokenType::ID, token.type());
            EXPECT_EQ(input + 19, token.begin());
            EXPECT_EQ(input + 20, token.end());
            token = pos->second[1];
            EXPECT_EQ(TokenType::ID, token.type());
            EXPECT_EQ(input + 22, token.begin());
            EXPECT_EQ(input + 23, token.end());
        }
        {
            Parser::DataPoints::const_iterator pos = dataPoints.find("2444");
            ASSERT_NE(dataPoints.end(), pos);
            EXPECT_EQ(std::string(input + 25, input + 29), pos->first);
            ASSERT_EQ(1u, pos->second.size());
            const Token& token = pos->second[0];
            EXPECT_EQ(TokenType::ID, token.type());
            EXPECT_EQ(input + 30, token.begin());
            EXPECT_EQ(input + 33, token.end());
        }
    }
}

TEST(Parser, handlesWhitespaceWithinBrackets)
{
    //                    012345678 90123456
    const char input[] = "A[Hello, \nworld!]";
    Lexer lexer(input);

    Parser::DataPoint dataPoint;
    bool success = false;
    ASSERT_NO_THROW(success = Parser::parseDataPoint(dataPoint, lexer));
    EXPECT_TRUE(success);

    EXPECT_EQ(std::string(input, input + 1), dataPoint.first);

    ASSERT_EQ(1u, dataPoint.second.size());
    const Token& token = *dataPoint.second.begin();
    EXPECT_EQ(TokenType::ID, token.type());
    EXPECT_EQ(input + 2, token.begin());
    EXPECT_EQ(input + 16, token.end());
}

TEST(Parser, handlesEscapedComments)
{
    //                    01234567 890123456
    const char input[] = "A[Hello,\\]world!]";
    Lexer lexer(input);

    Parser::DataPoint dataPoint;
    bool success = false;
    ASSERT_NO_THROW(success = Parser::parseDataPoint(dataPoint, lexer));
    EXPECT_TRUE(success);

    EXPECT_EQ(std::string(input, input + 1), dataPoint.first);

    ASSERT_EQ(1u, dataPoint.second.size());
    const Token& token = *dataPoint.second.begin();
    EXPECT_EQ(TokenType::ID, token.type());
    EXPECT_EQ(input + 2, token.begin());
    EXPECT_EQ(input + 16, token.end());
}

} // Close gobls
