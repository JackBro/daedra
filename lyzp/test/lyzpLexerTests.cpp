#include <lexer.h>
#include <gtest/gtest.h>

struct LexerIterSimpleTest
{
    LexerIterSimpleTest(const std::string& exp)
        : lexer(exp)
    {}

    size_t operator()()
    {
        for (const auto& token : lexer)
        {
            (void)token;
            tokens++;
        }

        return tokens;
    }

    lyzp::Lexer lexer;
    int tokens = 0;
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
