#include <buffer.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////
// Constructor tests
////////////////////////////////////////////////////////////////////////////////

TEST(BufferTestSuite, ctorTestCase1)
{
    lyzp::Buffer buf("");
    SUCCEED();
}

TEST(BufferTestSuite, ctorTestCase2)
{
    lyzp::Buffer buf("(");
    SUCCEED();
}

TEST(BufferTestSuite, ctorTestCase3)
{
    lyzp::Buffer buf("()");
    SUCCEED();
}

TEST(BufferTestSuite, ctorTestCase4)
{
    lyzp::Buffer buf("(def verbose-sum (x y) \"Sum any two numbers after printing a message.\" (+ x y))");
    SUCCEED();
}

TEST(BufferTestSuite, ctorTestCase5)
{
    lyzp::Buffer buf("(setq value true)");
    SUCCEED();
}


TEST(BufferTestSuite, ctorTestCase6)
{
    lyzp::Buffer buf("");
    ASSERT_TRUE(buf[0] == char(0));
    ASSERT_TRUE(buf[1] == char(0));
}


////////////////////////////////////////////////////////////////////////////////
// Subscripting operator tests
////////////////////////////////////////////////////////////////////////////////

TEST(BufferTestSuite, subscriptOpTestCase1)
{
    lyzp::Buffer buf("");
    try
    {
        buf[2];
        FAIL();
    }
    catch (std::out_of_range& ex)
    {
        SUCCEED();
    }
}

TEST(BufferTestSuite, subscriptOpTestCase2)
{
    lyzp::Buffer buf("");
    try
    {
        buf[-2];
        FAIL();
    }
    catch (std::out_of_range& ex)
    {
        SUCCEED();
    }
}

TEST(BufferTestSuite, subscriptOpTestCase3)
{
    lyzp::Buffer buf("()");
    EXPECT_EQ(buf[0], '(');
    EXPECT_EQ(buf[1], ')');
    EXPECT_EQ(buf[2], char(0));
    EXPECT_EQ(buf[3], char(0));
}

TEST(BufferTestSuite, subscriptOpTestCase4)
{
    lyzp::Buffer buf(" ()\n");
    EXPECT_EQ(buf[0], ' ');
    EXPECT_EQ(buf[1], '(');
    EXPECT_EQ(buf[2], ')');
    EXPECT_EQ(buf[3], '\n');
    EXPECT_EQ(buf[4], char(0));
    EXPECT_EQ(buf[5], char(0));
}
