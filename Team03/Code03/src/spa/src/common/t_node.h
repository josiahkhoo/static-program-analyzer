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

  TNode(TNode::Type type, int line_number, std::string string_val,
        std::vector<std::shared_ptr<TNode>> children);
  TNode(Type type, int line_number,
        std::vector<std::shared_ptr<TNode>> children);
  TNode(Type type, int line_number, int int_val);
  TNode(Type type, int line_number, std::string string_val);

  [[nodiscard]] int GetLineNumber() const;
  [[nodiscard]] std::vector<std::shared_ptr<TNode>> GetChildren() const;
  [[nodiscard]] Type GetType() const;
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
  bool operator==(const TNode& rhs) const;
  bool operator!=(const TNode& rhs) const;

 private:
  Type type_;
  int line_number_;
  std::vector<std::shared_ptr<TNode>> children_;
  std::optional<int> maybe_int_;
  std::optional<std::string> maybe_string_;
};

namespace std {
template <>
class hash<TNode> {
 public:
  /// Hash function for TNode using prime numbers 200771 and 300823 on the
  /// address. \param t_node \return size_t.
  size_t operator()(const TNode& t_node) const {
    auto u = (uintptr_t)&t_node;
    return (u * 200771) + (u % 300823);
  }
};
};  // namespace std

#endif  // SPA_T_NODE_H
