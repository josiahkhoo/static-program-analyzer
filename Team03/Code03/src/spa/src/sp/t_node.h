#ifndef SPA_T_NODE_H
#define SPA_T_NODE_H

#include <optional>
#include <vector>
#include <string>

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

  int GetLine();
  std::vector<TNode> GetChildren();
  Type GetType();
  std::optional<int> GetIntValue();
  std::optional<std::string> GetStringValue();
  bool IsStatement();
  bool IsExpression();
  bool IsOperator();
  bool IsLeaf();
};

#endif  // SPA_T_NODE_H
