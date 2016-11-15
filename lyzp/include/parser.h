#ifndef LYZP_PARSER_H
#define LYZP_PARSER_H

#include <lexer.h>

namespace lyzp
{

class Parser
{
public:
    Parser(const std::string& exp)
        : lexer(exp)
    {}

    void operator()()
    {
        for (const auto& tok : lexer)
        {
            print_token_info(tok);
        }
    }

    void print_token_info(const lyzp::Token& tok)
    {
        std::cout << "Kind: <" << static_cast<std::underlying_type<lyzp::TOKEN_KIND>::type>(tok.kind) << ">, "
                  << "Repr: <`" << tok.repr << "`>, "
                  << "Line: " << tok.line << ", "
                  << "Position: " << tok.position
                  << std::endl;
    }

private:
    Lexer lexer;
};

}

#endif  // End of LYZP_PARSER_H
