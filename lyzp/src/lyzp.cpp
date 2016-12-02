#include <evaluator.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "No expression to evaluate\n";
        return EXIT_FAILURE;
    }

    lyzp::Evaluator e(argv[1]);
    e.eval();

    return EXIT_SUCCESS;
}
