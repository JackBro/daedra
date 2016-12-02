#ifndef LYZP_PARSER_H
#define LYZP_PARSER_H

#include <list>
#include <algorithm>
#include <lexer.h>
#include <ast.h>


namespace lyzp
{

class Parser
{
public:
    Parser(const std::string& exp)
        : lexer(exp)
    {
        std::for_each(lexer.begin(), lexer.end(), [this](const auto& tok){ tokens.push_back(tok); });
        token_iter = tokens.begin();
    }

    void print_ast()
    {
        print_ast_node(ast);
    }

    void parse();

private:
    void expression(AstNode&);
    void list_expression(AstNode&);
    void function_call(AstNode&);
    void literal(AstNode&);
    void self_evaluating(AstNode&);
    void match(TOKEN_KIND);

    bool is_literal();
    bool is_operator(const Token&);

    const Token& next_token() const
    { 
        if (std::next(token_iter) == std::end(tokens))
        {
            static Token t;
            t.kind = TOKEN_KIND::EOI;
            return t; 
        }

        return *std::next(token_iter);
    }

    void print_ast_node(const AstNode& node, size_t ident = 0)
    {
        node.print(ident);

        for (auto& n : node.children)
            print_ast_node(*n, ident + 2);
    }

    Lexer lexer;
    ProgramNode ast;

    std::list<Token> tokens;
    std::list<Token>::iterator token_iter;
};

}

#endif  // End of LYZP_PARSER_H
