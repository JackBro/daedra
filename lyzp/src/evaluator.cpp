#include <evaluator.h>
#include <type_traits>

namespace lyzp
{

void Evaluator::eval()
{
    parser.parse();
    parser.print_ast();
    eval_dispatch(parser.get_ast());
}

void Evaluator::eval_dispatch(const AstNode& ast_node)
{
    std::cout << "Dispatching to evaluate node: " << ast_node.name() << "; typeid=`" << typeid(ast_node).name() << "`\n";

    if (std::string(ast_node.name()) == "Program")
        eval_node(dynamic_cast<const ProgramNode&>(ast_node));
    else if (std::string(ast_node.name()) == "Expression")
        eval_node(dynamic_cast<const ExpressionNode&>(ast_node));
    else if (std::string(ast_node.name()) == "OP")
        eval_node(dynamic_cast<const OpNode&>(ast_node));
}

}
