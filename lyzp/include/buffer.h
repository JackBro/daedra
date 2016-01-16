#ifndef LYZP_BUFFER_H
#define LYZP_BUFFER_H

#include <string>
#include <fstream>
#include <cstdint>
#include <stdexcept>

namespace lyzp
{

class Buffer
{
public:
    using value_type = uint8_t;

    Buffer(const std::string& input)
        : buf_size(input.size() + 2),
          buf(new value_type[buf_size])
    {
        for (size_t i = 0; i < input.size(); ++i)
            buf[i] = uint8_t(input[i]);

        buf[buf_size - 1] = char(0);
        buf[buf_size - 2] = char(0);
    }

    Buffer(const std::fstream input __attribute__ ((unused)))
    {
        //TODO: Implement this ctor as well
    }

    ~Buffer()
    {
        delete[] buf;
    }

    const value_type& operator[](size_t idx) const
    {
        if (idx >= buf_size)
            throw std::out_of_range("Index is out of range");

        return buf[idx];
    }

    Buffer(const Buffer& buf) = delete;
    Buffer& operator=(const Buffer& buf) = delete;

private:
    size_t buf_size;
    value_type* buf;
};

}

#endif  // End of LYZP_BUFFER_H
