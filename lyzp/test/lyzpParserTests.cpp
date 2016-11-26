#include <parser.h>
#include <gtest/gtest.h>

TEST(ParserTestSuite, ctorTestCase1)
{
    lyzp::Parser p("");
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase1)
{
    lyzp::Parser p("");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase2)
{
    lyzp::Parser p("()");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase2_1)
{
    lyzp::Parser p("(())");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase3)
{
    lyzp::Parser p("(()())");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase4)
{
    lyzp::Parser p("(()");
    try
    {
        p.parse();
        FAIL();
    }
    catch (std::domain_error& err)
    {
        SUCCEED();
    }
}

TEST(ParserTestSuite, parserTestCase5)
{
    lyzp::Parser p("(1)");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase5_1)
{
    lyzp::Parser p("(1 2)");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase5_2)
{
    lyzp::Parser p("(1) (2)");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase6)
{
    lyzp::Parser p("1 2 3 4");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserTestCase7)
{
    lyzp::Parser p("( (1) (2 3) (4) ((5 6 7) (8 9)))");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserOperatorTestCase1)
{
    lyzp::Parser p("(+ 1 2)");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, parserOperatorTestCase2)
{
    lyzp::Parser p("(- 3 2)");
    p.parse();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase1)
{
    lyzp::Parser p("");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase2)
{
    lyzp::Parser p("()");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase3)
{
    lyzp::Parser p("(1)");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase4)
{
    lyzp::Parser p("(1 2)");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase5)
{
    lyzp::Parser p("(+ 1 2)");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase6)
{
    lyzp::Parser p("1 2 3 4");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase7)
{
    lyzp::Parser p("((+) (1) (2))");
    p.parse();
    p.print_ast();
    SUCCEED();
}

TEST(ParserTestSuite, printAstTestCase8)
{
    lyzp::Parser p("(+ (- 2 1) (+ 3 4))");
    p.parse();
    p.print_ast();
    SUCCEED();
}
