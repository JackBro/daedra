#ifndef LYZP_TOKEN_H
#define LYZP_TOKEN_H

namespace lyzp
{

enum class TOKEN_KIND
{
    SOI,    // Start of input
    LEFT_PAREN,
    RIGHT_PAREN,
    INVALID,
    EOI     // End of input
};

struct Token
{
    Token()
        : kind(TOKEN_KIND::SOI), line(1), position(1)
    {}

    TOKEN_KIND kind;
    std::string repr;
    size_t line, position;
};

}

#endif  // End of LYZP_TOKEN_H
