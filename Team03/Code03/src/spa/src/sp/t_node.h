//
// Created by Josiah Khoo on 26/8/22.
//

#ifndef SPA_T_NODE_H
#define SPA_T_NODE_H

#include <optional>
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
  };

  int GetLine() const;
  std::vector<TNode> GetChildren() const;
  Type GetType() const;
  std::optional<int> GetIntValue() const;
  std::optional<std::string> GetStringValue() const;
  bool IsStatement() const;
  bool IsExpression() const;
  bool IsOperator() const;
  bool IsLeaf() const;
  bool IsType(Type type) const;
};

#endif  // SPA_T_NODE_H
