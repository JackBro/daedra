#include <evaluator.h>

namespace lyzp
{

void Evaluator::eval()
{
    parser.parse();
    parser.print_ast();
}

}
