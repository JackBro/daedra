#ifndef LYZP_TOKEN_H
#define LYZP_TOKEN_H

#include <iostream>


namespace lyzp
{

enum class TOKEN_KIND
{
    SOI             = 0,    // Start of input
    LEFT_PAREN      = 1,
    RIGHT_PAREN     = 2,
    PLUS            = 3,
    MINUS           = 4,
    NUMBER          = 5,
    INVALID,
    EOI                     // End of input
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

inline std::ostream& operator<<(std::ostream& os, const Token& tok)
{
    os << "Kind: <" << static_cast<std::underlying_type<lyzp::TOKEN_KIND>::type>(tok.kind) << ">, "
       << "Repr: <`" << tok.repr << "`>, "
       << "Line: " << tok.line << ", "
       << "Position: " << tok.position;

    return os;
}

}

#endif  // End of LYZP_TOKEN_H
