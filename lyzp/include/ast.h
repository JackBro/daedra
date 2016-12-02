#ifndef LYZP_AST_H
#define LYZP_AST_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>

namespace lyzp
{

struct AstNode
{
    using AstNodePtr = std::shared_ptr<AstNode>;
    std::vector<AstNodePtr> children;

    template <class T>
    AstNode& operator<<(const T& child)
    {
        children.emplace_back(std::make_shared<T>(child));
        //return *this;
        return *children.back().get();
    }

    virtual void print(size_t ident = 0) const
    {
        std::cout << to_str(ident);
    }

    virtual std::string to_str(size_t ident = 0, const std::string& value = "", const std::string& node_name = "AstNode: <`ROOT`>") const
    {
        std::string val = value.empty() ? "" : ": <`" + value + "`>";
        return std::string(ident, ' ') + "[" + node_name + val + ", children-count=" + std::to_string(children.size()) + "]\n";
    }
};

struct ProgramNode : AstNode
{
    ProgramNode(const std::string& name = "unnamed lyzp program")
        : prog_name(name)
    {}

    std::string prog_name;

    void print(size_t ident = 0) const override
    {
        std::cout << to_str(ident);
    }

    std::string to_str(size_t ident = 0, const std::string& value = "", const std::string& node_name = "Program") const override
    {
        return AstNode::to_str(ident, value, node_name);
    }
};

struct ExpressionNode : AstNode
{
    void print(size_t ident) const override
    {
        std::cout << to_str(ident);
    }

    std::string to_str(size_t ident = 0, const std::string& value = "", const std::string& node_name = "Expression") const override
    {
        return AstNode::to_str(ident, value, node_name);
    }
};

struct OpNode : AstNode
{
    OpNode(const std::string& name)
        : op_name(name)
    {}

    std::string op_name;

    void print(size_t ident = 0) const override
    {
        std::cout << to_str(ident, op_name);
    }

    std::string to_str(size_t ident = 0, const std::string& value = "", const std::string& node_name = "OP") const override
    {
        return AstNode::to_str(ident, value, node_name);
    }
};

struct LiteralNode : AstNode
{
    void print(size_t ident = 0) const override
    {
        std::cout << to_str(ident);
    }

    std::string to_str(size_t ident = 0, const std::string& value = "", const std::string& node_name = "Literal") const override
    {
        return AstNode::to_str(ident, value, node_name);
    }
};

struct NumberNode : LiteralNode
{
    NumberNode(int n)
        : number(n)
    {}

    int number;

    void print(size_t ident = 0) const override
    {
        std::cout << to_str(ident, std::to_string(number));
    }

    std::string to_str(size_t ident = 0, const std::string& value = "", const std::string& node_name = "Number") const override
    {
        return AstNode::to_str(ident, value, node_name);
    }
};

}

#endif  // End of LYZP_PARSER_H
