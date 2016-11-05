#include <lexer.h>
#include <gtest/gtest.h>

struct LexerIterSimpleTest
{
    LexerIterSimpleTest(const std::string& exp)
        : lexer(exp)
    {}

    size_t operator()()
    {
        for (const auto& tok : lexer)
        {
            token = tok;
            //std::cout << static_cast<std::underlying_type<lyzp::TOKEN_KIND>::type>(token.kind) << " " << token.repr << std::endl;
            tokens++;
        }

        return tokens;
    }

    lyzp::Lexer lexer;
    lyzp::Token token;
    size_t tokens = 0;
};

TEST(LexerTestSuite, iterTestCase1)
{
    std::string exp = "";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase2)
{
    std::string exp = "(";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase2_1)
{
    std::string exp = ")";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase3)
{
    std::string exp = "()";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase4)
{
    std::string exp = "(())";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase5)
{
    std::string exp = "(()(()()))";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase6)
{
    std::string exp = "(()(()()))(()(()()))";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), exp.size());
}

TEST(LexerTestSuite, iterTestCase7)
{
    LexerIterSimpleTest lex(" ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase8)
{
    LexerIterSimpleTest lex(" \t\n\v\f\r ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase9)
{
    LexerIterSimpleTest lex(" ( ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::LEFT_PAREN);
}

TEST(LexerTestSuite, iterTestCase9_1)
{
    LexerIterSimpleTest lex("\n ( \t");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::LEFT_PAREN);
}

TEST(LexerTestSuite, iterTestCase10)
{
    LexerIterSimpleTest lex(" ) ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::RIGHT_PAREN);
}

TEST(LexerTestSuite, iterTestCase10_1)
{
    LexerIterSimpleTest lex("\r )\f ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::RIGHT_PAREN);
}

TEST(LexerTestSuite, iterTestCase11)
{
    LexerIterSimpleTest lex("  \t\n\v\f\r (  \t\n\v\f\r ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::LEFT_PAREN);
}

TEST(LexerTestSuite, iterTestCase12)
{
    LexerIterSimpleTest lex("  \t\n\v\f\r    )     \t\n\v\f\r ");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::RIGHT_PAREN);
}

TEST(LexerTestSuite, iterTestCase13)
{
    std::string exp = "  \t\n\v\f\r    (     \t\n\v\f\r )    ";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 2);
}

TEST(LexerTestSuite, iterTestCase14)
{
    std::string exp = "   (  (\t)) \t \n \v  \f\r    (     \t\n\v\f\r )    ";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 6);
}

TEST(LexerTestSuite, iterTestCase15)
{
    std::string exp = "\n( () \t ( ( \r )( )  )   )     (() ( ()() )   )  ";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 20);
}

TEST(LexerTestSuite, iterTestCase16)
{
    std::string exp = "\n(\n(\t(\t) )\r)\r \v(\v)\f\f   \n";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 8);
}

TEST(LexerTestSuite, iterTestCase17)
{
    std::string exp = "   (() ()) ";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 6);
}
