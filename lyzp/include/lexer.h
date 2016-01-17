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
        : buf(exp)
    {}

    class iterator
    {
    public:
        // Constructor for our 'begin' iterator
        explicit iterator(const Buffer& b)
            : buf(b)
        {}

        // Constructor for our 'end' iterator
        explicit iterator(const Buffer& b, size_t s)
            : buf(b), index(s)
        {}

        bool operator==(const iterator& other) const
        {
            return (buf[index] == char(0) && buf[index + 1] == char(0)
                        && other.buf[other.index - 2] == char(0) && other.buf[other.index - 1] == char(0));
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        iterator& operator++()
        {
            index++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator it(*this);
            ++(*this);
            return it;
        }

        Buffer::value_type operator*() const { return buf[index]; }
        const Buffer::value_type* operator->() const { return &buf[index]; }

    private:
        const Buffer& buf;
        size_t index = 0;
    };  // End of iterator
        
    iterator begin() { return iterator(buf); }
    iterator end()   { return iterator(buf, buf.size()); }

private:
    Buffer buf;
};

}

#endif  // End of LYZP_LEXER_H
