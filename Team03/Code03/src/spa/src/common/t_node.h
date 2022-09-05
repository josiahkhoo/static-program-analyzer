#ifndef SPA_T_NODE_H
#define SPA_T_NODE_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

class TNode {
public:
    enum Type {
        Program,
        Procedure,
        StatementList,
        Assign,
        Call,
        IfElseThen,
        Print,
        Read,
        While,
        Not,
        And,
        Or,
        Inverse,
        Greater,
        GreaterThanEqual,
        Lesser,
        LesserThanEqual,
        Equal,
        NotEqual,
        Plus,
        Minus,
        Multiply,
        Divide,
        Modulo,
        Variable,
        Constant,
        Invalid
    };

    TNode(int id, TNode::Type type, std::string string_val,
          std::vector<std::shared_ptr<TNode>> children);

    TNode(int id, TNode::Type type, std::vector<std::shared_ptr<TNode>> children);

    TNode(int id, TNode::Type type, int statement_number,
          std::vector<std::shared_ptr<TNode>> children);

    TNode(int id, TNode::Type type, int statement_number, int int_val);

    TNode(int id, TNode::Type type, int statement_number, std::string string_val);

    [[nodiscard]] int GetStatementNumber() const;

    [[nodiscard]] std::vector<std::shared_ptr<TNode>> GetChildren() const;

    [[nodiscard]] Type GetType() const;

    [[nodiscard]] int GetId() const;

    [[nodiscard]] int GetIntValue() const;

    [[nodiscard]] std::string GetStringValue() const;

    [[nodiscard]] bool IsStatement() const;

    [[nodiscard]] bool IsEqualityOperator() const;

    [[nodiscard]] bool IsLogicalOperator() const;

    [[nodiscard]] bool IsPlusMinusOperator() const;

    [[nodiscard]] bool IsTimesDivideQuotientOperator() const;

    [[nodiscard]] bool IsLeaf() const;

    [[nodiscard]] bool IsType(Type type) const;

    [[nodiscard]] bool IsNotType(Type type) const;

    bool operator==(const TNode &rhs) const;

    bool operator!=(const TNode &rhs) const;

private:
    Type type_;
    std::optional<int> statement_number_;
    int unique_id_;
    std::vector<std::shared_ptr<TNode>> children_;
    std::optional<int> maybe_int_;
    std::optional<std::string> maybe_string_;
};

namespace std {
    template<>
    class hash<TNode> {
    public:
        /// Hash function for TNode using prime numbers 200771 and 300823 on the
        /// address. \param t_node \return size_t.
        size_t operator()(const TNode &t_node) const {
            return (t_node.GetId() * 200771) + (t_node.GetType() % 300823);
        }
    };
};  // namespace std

#endif  // SPA_T_NODE_H
