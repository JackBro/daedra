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
                set_token(TOKEN_KIND::EOI, "", false);
                return;
            }

            if (buf[index] == '(')
                set_token(TOKEN_KIND::LEFT_PAREN, "(");
            else if (buf[index] == ')')
                set_token(TOKEN_KIND::RIGHT_PAREN, ")");
            else if (buf[index] == '+' && isdigit(peek()))
                scan_number();
            else if (buf[index] == '+')
                set_token(TOKEN_KIND::PLUS, "+");
            else if (buf[index] == '-' && isdigit(peek()))
                scan_number();
            else if (buf[index] == '-')
                set_token(TOKEN_KIND::MINUS, "-");
            else if (isdigit(buf[index]))
                scan_number();
            else
                set_token(TOKEN_KIND::INVALID, std::string(1, buf[index]), false);
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

            while (buf[index] != '\n' && !is_eoi()) 
                index++;

            if (is_eoi())
                set_token(TOKEN_KIND::EOI, "", false);
        }

        void scan_number()
        {
            /////////////////////////////////////////////////////////////////////////////
            // TODO: Handle case like this:
            // 1a2
            /////////////////////////////////////////////////////////////////////////////
            std::string sign;
            if (buf[index] == '+' || buf[index] == '-')
            {
                sign += buf[index]; 
                index++;
            }

            std::string number = sign;
            while (isdigit(buf[index]))
            {
                number += buf[index];
                index++;
            }

            // When we set token here, don't increment the index,
            // for buf[index] is not a digit anymore, it's a different character
            if (is_delimiter())
            {
                set_token(TOKEN_KIND::NUMBER, number, false);
                return;
            }

            position += number.size();
            set_token(TOKEN_KIND::INVALID, std::string(1, buf[index]), true);
        } 

        Buffer::value_type peek() const { return buf[index + 1]; }

        bool is_eoi() { return buf[index] == char(0); }

        bool is_delimiter() const
        {
            static std::string delimiters = "();\"'`|[]{} \n\t\v\f\r" + std::string(1, char(0));
            return delimiters.find(buf[index]) != std::string::npos;
        }

        void set_token(TOKEN_KIND kind, const std::string& repr = "", bool increment = true)
        {
            token.kind = kind;
            token.repr = repr;
            token.line = line;
            token.position = position;

            if (increment)
                index++;
 
            position += repr.size();
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
