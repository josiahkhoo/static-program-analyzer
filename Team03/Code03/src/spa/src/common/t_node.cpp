#include "t_node.h"

#include <utility>

TNode::TNode(TNode::Type type, int line_number,
             std::vector<std::shared_ptr<TNode>> children)
    : type_(type), line_number_(line_number), children_(std::move(children)) {}

TNode::TNode(TNode::Type type, int line_number, int int_val)
    : type_(type), line_number_(line_number), maybe_int_(int_val) {}

TNode::TNode(TNode::Type type, int line_number, std::string string_val)
    : type_(type), line_number_(line_number), maybe_string_(string_val) {}

int TNode::GetLine() const { return line_number_; }

std::vector<std::shared_ptr<TNode>> TNode::GetChildren() const {
  return children_;
}

TNode::Type TNode::GetType() const { return type_; }

int TNode::GetIntValue() const {
  assert(IsType(Constant) && maybe_int_.has_value());
  return maybe_int_.value();
}

std::string TNode::GetStringValue() const {
  assert(IsType(Program) || IsType(Procedure) || IsType(Variable));
  assert(maybe_string_.has_value());
  return maybe_string_.value();
}

bool TNode::IsStatement() const {
  return IsType(Assign) || IsType(Call) || IsType(IfElseThen) ||
         IsType(Print) || IsType(Read) || IsType(While);
}

bool TNode::IsEqualityOperator() const {
  return IsType(Greater) || IsType(GreaterThanEqual) || IsType(Lesser) ||
         IsType(LesserThanEqual) || IsType(Equal) || IsType(NotEqual);
}

bool TNode::IsLogicalOperator() const {
  return IsType(And) || IsType(Or) || IsType(Inverse);
}

bool TNode::IsPlusMinusOperator() const {
  return IsType(Plus) || IsType(Minus);
}

bool TNode::IsTimesDivideQuotientOperator() const {
  return IsType(Multiply) || IsType(Divide) || IsType(Modulo);
}

bool TNode::IsLeaf() const { return IsType(Variable) || IsType(Constant); }

bool TNode::IsType(TNode::Type type) const { return type_ == type; }

bool TNode::IsNotType(TNode::Type type) const { return !IsType(type); }
