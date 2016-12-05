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
    virtual ~AstNode() {}

    using AstNodePtr = std::shared_ptr<AstNode>;
    std::vector<AstNodePtr> children;
    static constexpr const char* node_name = "AST-ROOT-NODE";

    template <class T>
    AstNode& operator<<(const T& child)
    {
        children.emplace_back(std::make_shared<T>(child));
        //return *this;
        return *children.back().get();
    }

    virtual const char* name() const { return node_name; }

    virtual void print(size_t ident = 0) const
    {
        std::cout << to_str(ident);
    }

    virtual std::string to_str(size_t ident = 0) const { return to_str(node_name, "", ident); } 
    virtual std::string to_str(const std::string& name, const std::string& value = "", size_t ident = 0) const
    {
        std::string val = value.empty() ? "" : ": <`" + value + "`>";
        return std::string(ident, ' ') + "[" + name + val + ", children-count=" + std::to_string(children.size()) + "]\n";
    }
};

struct ProgramNode : AstNode
{
    ProgramNode(const std::string& name = "unnamed lyzp program")
        : prog_name(name)
    {}

    static constexpr const char* node_name = "Program";
    std::string prog_name;

    const char* name() const override { return node_name; }
    void print(size_t ident = 0) const override { std::cout << to_str(ident); }
    std::string to_str(size_t ident = 0) const override { return AstNode::to_str(node_name, prog_name, ident); }
};

struct ExpressionNode : AstNode
{
    static constexpr const char* node_name = "Expression";

    const char* name() const override { return node_name; }
    void print(size_t ident = 0) const override { std::cout << to_str(ident); }
    std::string to_str(size_t ident = 0) const override { return AstNode::to_str(node_name, "", ident); }
};

struct OpNode : AstNode
{
    OpNode(const std::string& name)
        : op_name(name)
    {}

    static constexpr const char* node_name = "OP";
    std::string op_name;

    const char* name() const override { return node_name; }
    void print(size_t ident = 0) const override { std::cout << to_str(ident); }
    std::string to_str(size_t ident = 0) const override { return AstNode::to_str(node_name, op_name, ident); }
};

struct LiteralNode : AstNode
{
    static constexpr const char* node_name = "Literal";

    const char* name() const override { return node_name; }
    void print(size_t ident = 0) const override { std::cout << to_str(ident); }
    std::string to_str(size_t ident = 0) const override { return AstNode::to_str(node_name, "", ident); }
};

struct NumberNode : LiteralNode
{
    NumberNode(int n)
        : number(n)
    {}

    static constexpr const char* node_name = "Number";
    int number;

    const char* name() const override { return node_name; }
    void print(size_t ident = 0) const override { std::cout << to_str(ident); }
    std::string to_str(size_t ident = 0) const override { return AstNode::to_str(node_name, std::to_string(number), ident); }
};

}

#endif  // End of LYZP_PARSER_H
