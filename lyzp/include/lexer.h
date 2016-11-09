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
            skip();
            recognize_token();
        }

        void recognize_token()
        {
            if (buf[index] == char(0))
            {
                set_token(TOKEN_KIND::EOI);
                return;
            }

            if (buf[index] == '(')
                set_token(TOKEN_KIND::LEFT_PAREN, "(", true);
            else if (buf[index] == ')')
                set_token(TOKEN_KIND::RIGHT_PAREN, ")", true);
            else if (buf[index] == '+')
                set_token(TOKEN_KIND::PLUS, "+", true);
            else
                set_token(TOKEN_KIND::INVALID, std::string(1, buf[index]), true);
        }

        void skip()
        {
            for (;;)
            {
                skip_comment();
                skip_whitespace();

                if (buf[index] != ';')
                    return;
            }
        }

        void skip_whitespace()
        {
            while (isspace(buf[index]))
            {
                if (buf[index] == '\n')
                {
                    line++;
                    position = 0;
                }

                index++;
                position++;
            }
        }

        void skip_comment()
        {
            if (buf[index] != ';')
                return;

            while (buf[index] != '\n' && buf[index] != char(0)) 
                index++;

            if (buf[index] == char(0))
                set_token(TOKEN_KIND::EOI);
        }

        void set_token(TOKEN_KIND kind, const std::string& repr = "", bool increment = false)
        {
            token.kind = kind;
            token.repr = repr;
            token.line = line;
            token.position = position;

            if (increment)
            {
                index++;
                position++;
            }
        }

        const Buffer& buf;
        size_t index = 0;
        size_t line = 1;
        size_t position = 1;
        Token token;
    };  // End of iterator
        
    iterator begin() { return iterator(buf); }
    iterator end()   { return iterator(buf, buf.size()); }

private:
    Buffer buf;
};

}

#endif  // End of LYZP_LEXER_H
