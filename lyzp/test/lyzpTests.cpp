#include <lexer.h>
#include <gtest/gtest.h>

TEST(LexerTestSuite, testCase1)
{
    lyzp::Lexer lexer("");
    EXPECT_TRUE(true);
}

TEST(LexerTestSuite, testCase2)
{
    lyzp::Lexer lexer("");
    EXPECT_TRUE(true);
}

// Run all the tests that were declared with TEST()
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
