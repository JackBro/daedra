#ifndef LYZP_EVALUATOR_H
#define LYZP_EVALUATOR_H

#include <parser.h>


namespace lyzp
{

class Evaluator
{
public:
    Evaluator(const std::string& exp)
        : parser(exp)
    {}

    void eval();

private:
    Parser parser;
};

}

#endif
