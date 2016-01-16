#ifndef LYZP_TOKEN_H
#define LYZP_TOKEN_H

namespace lyzp
{

struct LeftParenTokenType;
struct RightParenTokenType;

template<class TokenType> struct Token;
template<> struct Token<LeftParenTokenType> {};
template<> struct Token<RightParenTokenType> {};

}

#endif  // End of LYZP_TOKEN_H
