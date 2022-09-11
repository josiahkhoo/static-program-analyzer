#include "pattern_statement_entity.h"

#include <cassert>

PatternStatementEntity::PatternStatementEntity(const TNode& node,
                                               int statement_number)
    : StatementEntity(node, statement_number) {}

std::string PatternStatementEntity::GetLeftHandSidePattern() const {
  return GetPatternSourceNode().GetChildren()[0]->GetStringValue();
}

std::string PatternStatementEntity::GetRightHandSidePattern() const {
  return RecursivelyFlatten(*GetPatternSourceNode().GetChildren()[1]);
}

std::string PatternStatementEntity::RecursivelyFlatten(
    const TNode& node) const {
  if (node.IsType(TNode::Constant)) {
    return "(" + std::to_string(node.GetIntValue()) + ")";
  } else if (node.IsType(TNode::Variable)) {
    return "(" + node.GetStringValue() + ")";
  }

  assert(node.IsTimesDivideQuotientOperator() || node.IsPlusMinusOperator());
  std::string op;
  if (node.IsType(TNode::Plus)) {
    op = "+";
  } else if (node.IsType(TNode::Minus)) {
    op = "-";
  } else if (node.IsType(TNode::Multiply)) {
    op = "*";
  } else if (node.IsType(TNode::Divide)) {
    op = "/";
  } else if (node.IsType(TNode::Modulo)) {
    op = "%";
  }
  return "(" + RecursivelyFlatten(*node.GetChildren()[0]) + op +
         RecursivelyFlatten(*node.GetChildren()[1]) + ")";
}
