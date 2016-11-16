#include <parser.h>

int main(int argc __attribute__ ((unused)), char** argv __attribute__ ((unused)))
{
    lyzp::Parser("(- (+ 1 2 3) (+ 4 5))")();
    return EXIT_SUCCESS;
}
