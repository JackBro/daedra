#ifndef LYZP_LEXER_H
#define LYZP_LEXER_H

#include <string>
#include <token.h>
#include <buffer.h>
#include <iostream>

namespace lyzp
{

class Lexer
{
public:
    Lexer(const std::string& exp)
        : buf(exp)
    {}

    class iterator
    {
    public:
        // Constructor for our 'begin' iterator
        explicit iterator(const Buffer& b)
            : buf(b)
        {
            advance(); 
        }

        // Constructor for our 'end' iterator
        explicit iterator(const Buffer& b, size_t s)
            : buf(b), index(s)
        {
            token.kind = TOKEN_KIND::EOI;
        }

        bool operator==(const iterator& other) const
        {
            return token.kind == other.token.kind;
            //return (buf[index] == char(0) && buf[index + 1] == char(0)
            //            && other.buf[other.index - 2] == char(0) && other.buf[other.index - 1] == char(0));
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        iterator& operator++()
        {
            advance();
            return *this;
        }

        iterator operator++(int)
        {
            iterator it(*this);
            ++(*this);
            return it;
        }

        Token operator*() const { return token; }
        const Token* operator->() const { return &token; }

    private:
        void advance()
        { 
            skip_whitespace();

            if (buf[index] == char(0))
            {
                token.kind = TOKEN_KIND::EOI;
                token.repr = "";
                return;
            }

            if (buf[index] == '(')
            {
                token.kind = TOKEN_KIND::LEFT_PAREN;
                token.repr = "(";
            }
            else if (buf[index] == ')')
            {
                token.kind = TOKEN_KIND::RIGHT_PAREN;
                token.repr = ")";
            }

            index++;
        }

        void skip_whitespace()
        {
            while (isspace(buf[index]))
                index++;
        }

        const Buffer& buf;
        size_t index = 0;
        Token token;
    };  // End of iterator
        
    iterator begin() { return iterator(buf); }
    iterator end()   { return iterator(buf, buf.size()); }

private:
    Buffer buf;
};

}

#endif  // End of LYZP_LEXER_H
