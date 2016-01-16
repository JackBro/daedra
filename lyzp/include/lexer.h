#ifndef LYZP_LEXER_H
#define LYZP_LEXER_H

#include <string>
#include <token.h>
#include <buffer.h>

namespace lyzp
{

class Lexer
{
public:
    Lexer(const std::string& exp)
        : idx(0), buf(exp)
    {}

private:
    size_t idx;
    Buffer buf;
};

}

#endif  // End of LYZP_LEXER_H
