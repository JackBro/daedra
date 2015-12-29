#include <parser.h>

int main(int argc __attribute__ ((unused)), char** argv __attribute__ ((unused)))
{
    lyzp::Parser("()")();
    return EXIT_SUCCESS;
}
