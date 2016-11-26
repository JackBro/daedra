#include <parser.h>
#include <sstream>

namespace lyzp
{

void Parser::parse()
{
    ProgramNode prog("lyzp program");
    while (token_iter != std::end(tokens))
        expression(prog);
    ast << prog;
}

void Parser::expression(AstNode& ast_node)
{
    // <expression> --> <variable> | <literal> | <procedure call>
    std::cout << __func__ << ": current token: " << *token_iter << "\n";
    ExpressionNode exp_node;

    if (token_iter->kind == TOKEN_KIND::LEFT_PAREN)
    {
        match(TOKEN_KIND::LEFT_PAREN);
        list_expression(exp_node);
        match(TOKEN_KIND::RIGHT_PAREN);
    }
    else if (is_literal())
        literal(exp_node);
    else
        throw std::domain_error("Bad expression");

    ast_node << exp_node;
}

void Parser::list_expression(AstNode& ast_node)
{
    std::cout << __func__ << ": current token: " << *token_iter << "\n";

    if (is_operator(*token_iter))
        function_call(ast_node);

    while (token_iter->kind != TOKEN_KIND::RIGHT_PAREN && token_iter != std::end(tokens))
        expression(ast_node);
}

void Parser::literal(AstNode& ast_node)
{
    LiteralNode lit_node;
    self_evaluating(lit_node);
    ast_node << lit_node;
}

void Parser::self_evaluating(AstNode& ast_node)
{
    // <self-evaluating> --> <boolean> | <number> | <character> | <string>
    ast_node << NumberNode(std::stoi(token_iter->repr));
    match(TOKEN_KIND::NUMBER);
}

void Parser::function_call(AstNode& ast_node)
{
    // <function call> --> `(` <operator> <operand>* `)`
    ast_node << OpNode(token_iter->repr);
    match(token_iter->kind);
}

void Parser::match(TOKEN_KIND kind)
{
    if (token_iter == std::end(tokens))
        throw std::domain_error("Expected valid token but end-of-input encountered");

    std::cout << __func__ << ": " << *token_iter << "\n";

    if (token_iter->kind != kind)
    {
        std::stringstream ss;
        ss << *token_iter;
        throw std::domain_error("Unxpected token: " + ss.str());
    }

    token_iter++;
}

bool Parser::is_literal()
{
    return token_iter->kind == TOKEN_KIND::NUMBER;
}

bool Parser::is_operator(const Token& t)
{
    return (t.kind == TOKEN_KIND::PLUS || t.kind == TOKEN_KIND::MINUS);
}

}
