#ifndef LYZP_AST_H
#define LYZP_AST_H

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

namespace lyzp
{

struct AstNode
{
    using AstNodePtr = std::shared_ptr<AstNode>;
    std::vector<AstNodePtr> children;

    template <class T>
    AstNode& operator<<(const T& child)
    {
        auto ch = std::make_shared<T>(child);
        children.emplace_back(ch);
        return *this;
    }

    virtual void print(size_t ident __attribute__ ((unused)) = 0) const
    {
        std::cout << std::string(ident, '-') << "[AstNode: <`ROOT`>]\n";
    }
};

struct ProgramNode : AstNode
{
    ProgramNode(const std::string& name)
        : prog_name(name)
    {}

    std::string prog_name;

    void print(size_t ident) const override
    {
        std::cout << std::string(ident, ' ') << "[Program: <`" << prog_name << "`>, children-count=" << children.size() << "]\n";
    }
};

struct ExpressionNode : AstNode
{
    void print(size_t ident) const override
    {
        std::cout << std::string(ident, ' ') << "[Expression: children-count=" << children.size() << "]\n";
    }
};

struct OpNode : AstNode
{
    OpNode(const std::string& name)
        : op_name(name)
    {}

    std::string op_name;

    void print(size_t ident) const override
    {
        std::cout << std::string(ident, ' ') << "[OP: <`" << op_name << "`>, children-count=" << children.size() << "]\n";
    }
};

struct LiteralNode : AstNode
{
    void print(size_t ident) const override
    {
        std::cout << std::string(ident, ' ') << "[Literal: children-count=" << children.size() << "]\n";
    }
};

struct NumberNode : LiteralNode
{
    NumberNode(int n)
        : number(n)
    {}

    int number;

    void print(size_t ident) const override
    {
        std::cout << std::string(ident, ' ') << "[Number: <`" << number << "`>, children-count=" << children.size() << "]\n";
    }
};

}

#endif  // End of LYZP_PARSER_H
