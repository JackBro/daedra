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
            /*
            std::cout << static_cast<std::underlying_type<lyzp::TOKEN_KIND>::type>(token.kind)
                      << " " << token.repr
                      << " (" << (int)token.repr[0] << ")"
                      << std::endl;
            */
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

TEST(LexerTestSuite, iterTestCase2_2)
{
    LexerIterSimpleTest lex(")");
    lex();
    EXPECT_EQ(lex.token.line, 1);
    EXPECT_EQ(lex.token.position, 1);
}

TEST(LexerTestSuite, iterTestCase2_3)
{
    LexerIterSimpleTest lex(" )");
    lex();
    EXPECT_EQ(lex.token.line, 1);
    EXPECT_EQ(lex.token.position, 2);
}

TEST(LexerTestSuite, iterTestCase2_4)
{
    LexerIterSimpleTest lex("\n)");
    lex();
    EXPECT_EQ(lex.token.line, 2);
    EXPECT_EQ(lex.token.position, 1);
}

TEST(LexerTestSuite, iterTestCase2_5)
{
    LexerIterSimpleTest lex("\n\n   )");
    lex();
    EXPECT_EQ(lex.token.line, 3);
    EXPECT_EQ(lex.token.position, 4);
}

TEST(LexerTestSuite, iterTestCase2_6)
{
    std::string exp =
        ";;;;;;;;;;;;;;;;;;;;;;;;;;######;;;;;;;;;;;;;;;;;;;;;;;;   \n"
        ";; (ANOTHER COMMENT TEST)                                  \n"
        ";;;;;;;;;;;;;;;;;;;;;;;;;;######;;;;;;;;;;;;;;;;;;;;;;;;   \n"
        "                    \t)    ;;;;  ()                        \n"
        ";;;; Single token ----^                                    \n"
        ;
    LexerIterSimpleTest lex(exp);
    lex();
    EXPECT_EQ(lex.token.line, 4);
    EXPECT_EQ(lex.token.position, 22);
}

TEST(LexerTestSuite, iterTestCase2_7)
{
    std::string exp =
        "                                                                               )";
    LexerIterSimpleTest lex(exp);
    lex();
    EXPECT_EQ(lex.token.line, 1);
    EXPECT_EQ(lex.token.position, 80);
}

TEST(LexerTestSuite, iterTestCase2_8)
{
    std::string exp = "\n\t\n  \n;\n  \n\n\n\n         (";
    LexerIterSimpleTest lex(exp);
    lex();
    EXPECT_EQ(lex.token.line, 9);
    EXPECT_EQ(lex.token.position, 10);
}

TEST(LexerTestSuite, iterTestCase2_9)
{
    std::string exp = "\n\t\n  \n;\n  \n\n\n\n\n(";
    LexerIterSimpleTest lex(exp);
    lex();
    EXPECT_EQ(lex.token.line, 10);
    EXPECT_EQ(lex.token.position, 1);
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

TEST(LexerTestSuite, iterTestCase18)
{
    LexerIterSimpleTest lex(";");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase19)
{
    LexerIterSimpleTest lex(";\n");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase20)
{
    LexerIterSimpleTest lex(";;;;;;;;;");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase21)
{
    LexerIterSimpleTest lex(";()");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase22)
{
    LexerIterSimpleTest lex(";; 10 ; Atom");
    lex();
    EXPECT_TRUE(lex.token.kind == lyzp::TOKEN_KIND::SOI);
}

TEST(LexerTestSuite, iterTestCase23)
{
    EXPECT_EQ(LexerIterSimpleTest("() ; ()")(), 2);
}

TEST(LexerTestSuite, iterTestCase23_1)
{
    EXPECT_EQ(LexerIterSimpleTest("\t()\t ; \f ()")(), 2);
}

TEST(LexerTestSuite, iterTestCase23_2)
{
    EXPECT_EQ(LexerIterSimpleTest(" \t \n \v \f \r () \t ; \t \v \r \f (42)")(), 2);
}

TEST(LexerTestSuite, iterTestCase24)
{
    EXPECT_EQ(LexerIterSimpleTest("; (do-something a)       ; Comments indented at column 40, or the last")(), 0);
}

TEST(LexerTestSuite, iterTestCase25)
{
    EXPECT_EQ(LexerIterSimpleTest(";\n()")(), 2);
}

TEST(LexerTestSuite, iterTestCase26)
{
    std::string exp =
        ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
        ";; COMMENT TEST\n"
        ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 0);
}

TEST(LexerTestSuite, iterTestCase27)
{
    std::string exp =
        "(\n"
        "; this \"Canonical S-expression\" has 5 atoms"
        "\n)";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 2);
}

TEST(LexerTestSuite, iterTestCase28)
{
    std::string exp =
    "    ;  ()     \t\n\v\f\r    \n"
    "    (          ;     )      \n"
    "    )          ;     )      \n"
    "    ()                      \n"
    "    (          ;     ()     \n"
    "    )          ;     (;)    \n";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 6);
}

TEST(LexerTestSuite, iterTestCase29)
{
    std::string exp =
        "; one semi-colon                               \n"
        ";; two semi-colons                             \n"
        ";;; three semi-colons                          \n" 
        ";;;; four semi-colons                          \n"
        ";;;;; five semi-colons                         \n"
        ";;;;;; six semi-colons                         \n"
        ";;;;;;;; seven semi-colons                     \n"
        ";;;;;;;; eight semi-colons                     \n"
        ";;;;;;;;; nine semi-colons                     \n"
        ";;;;;;;;;; ten semi-colons                     \n"
        "                                               \n"
        "     () ; empty list                           \n"
        "                                               \n"
        "; one semi-colon ;                             \n"
        ";; two semi-colons ;;                          \n"
        ";;; three semi-colons ;;;                      \n"
        ";;;; four semi-colons ;;;;                     \n"
        ";;;;; five semi-colons ;;;;;                   \n"
        ";;;;;; six semi-colons ;;;;;;                  \n"
        ";;;;;;;; eight semi-colons ;;;;;;;;            \n"
        ";;;;;;;;; nine semi-colons ;;;;;;;;;           \n"
        ";;;;;;;;;; ten semi-colons ;;;;;;;;;;          \n";
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 2);
}

TEST(LexerTestSuite, iterTestCase30)
{
    std::string exp =
        ";;;;;;;;;;;;;;;;;;;;;;;;;;######;;;;;;;;;;;;;;;;;;;;;;;;   \n"
        ";; (ANOTHER COMMENT TEST)                                  \n"
        ";;;;;;;;;;;;;;;;;;;;;;;;;;######;;;;;;;;;;;;;;;;;;;;;;;;   \n"
        "                   (\t)    ;;;;  ()                        \n"
        ";;;; First token --^  ^-- Second token                     \n"
        ";;;; -----                                                 \n"
        ";;;; At the top of source files (four semi-colons)         \n"
        ";;;  Comments at the beginning of the line (3 semi-colons) \n"
        ";;   Comments indented along with code (2 semi-colons)     \n" 
        ";(do-something a)                      ; Comments indented at column 40, or the last  \n"
        ";  (do-something-else b))              ; column + 1 space if line exceeds 38 columns  \n"
        ";; ()                                                      \n"
        ";;; (1)                                                    \n"
        " ;;;; __some-string__                                      \n"
        ";; 10 ; Atom                                               \n"
        "; Commented out line ;                                     \n"
        "  ; commenting (until end of line)                         \n"
        "    ; another comment                                      \n"
        "      ; yet another comment                                \n"
        "           ; comment indented with tabs                    \n"
        "               ; '()                                       \n"
        "                 ;  ( () )                                 \n"
        "           ;        ( (0) )                                \n"
        " ;;;                                                       \n"
        " (     ); () empty list                                    \n"
        ";^-----^----- Third and fourth tokens                      \n"
        ;
    EXPECT_EQ(LexerIterSimpleTest(exp)(), 4);
}
