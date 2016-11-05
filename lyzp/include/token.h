#ifndef LYZP_TOKEN_H
#define LYZP_TOKEN_H

namespace lyzp
{
/*
struct LeftParenTokenType;
struct RightParenTokenType;

template<class TokenType> struct Token;
template<> struct Token<LeftParenTokenType> {};
template<> struct Token<RightParenTokenType> {};
*/
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
        : kind(TOKEN_KIND::SOI)
    {}

    TOKEN_KIND kind;
    std::string repr;
};

}

#endif  // End of LYZP_TOKEN_H
