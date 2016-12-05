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

    void eval_dispatch(const AstNode&);

    template<class T>
    void eval_node(const T& node);

    Parser parser;
};

template<>
inline
void Evaluator::eval_node<ProgramNode>(const ProgramNode& node)
{
    std::cout << __func__ << ": Evaluating: " << typeid(node).name() << "\n";
    //std::cout << " : " << node.prog_name << "\n";

    for (auto& n : node.children)
        eval_dispatch(*n);
}

template<>
inline
void Evaluator::eval_node<ExpressionNode>(const ExpressionNode& node)
{
    std::cout << __func__ << ": Evaluating: " << typeid(node).name() << "\n";
    std::cout << " : " << node.node_name << "\n";

    for (auto& n : node.children)
        eval_dispatch(*n); 
}

template<>
inline
void Evaluator::eval_node<OpNode>(const OpNode& node)
{
    std::cout << "Evaluating: " << typeid(node).name() << "\n";
    std::cout << " : " << node.op_name << "\n";

    for (auto& n : node.children)
        eval_dispatch(*n); 
}

}

#endif
