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
            std::cout << tok << "\n";  
        }
    }

private:
    Lexer lexer;
};

}

#endif  // End of LYZP_PARSER_H
