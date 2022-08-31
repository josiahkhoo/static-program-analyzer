#include "t_node.h"

#include <cassert>
#include <utility>

TNode::TNode(int id, TNode::Type type, std::string string_val,
             std::vector<std::shared_ptr<TNode>> children)
    : unique_id_(id),
      type_(type),
      maybe_string_(string_val),
      children_(std::move(children)) {}

TNode::TNode(int id, TNode::Type type,
             std::vector<std::shared_ptr<TNode>> children)
    : unique_id_(id), type_(type), children_(std::move(children)) {}

TNode::TNode(int id, TNode::Type type, int statement_number,
             std::vector<std::shared_ptr<TNode>> children)
    : unique_id_(id), type_(type),
      statement_number_(statement_number), children_(std::move(children)) {}

TNode::TNode(int id, TNode::Type type, int statement_number, int int_val)
    : unique_id_(id), type_(type), statement_number_(statement_number), maybe_int_(int_val) {}

TNode::TNode(int id, TNode::Type type, int statement_number, std::string string_val)
    : unique_id_(id), type_(type), statement_number_(statement_number), maybe_string_(string_val) {}

int TNode::GetStatementNumber() const {
  assert(statement_number_.has_value());
  return statement_number_.value();
}

std::vector<std::shared_ptr<TNode>> TNode::GetChildren() const {
  if (IsType(Inverse) || IsType(Print) || IsType(Read)) {
    assert(children_.size() == 1);
  } else if (IsType(While) || IsType(Assign) || IsEqualityOperator() ||
             IsLogicalOperator() || IsTimesDivideQuotientOperator()) {
    assert(children_.size() == 2);
  } else if (IsType(IfElseThen)) {
    assert(children_.size() == 3);
  }
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

bool TNode::operator==(const TNode& rhs) const {
  return type_ == rhs.type_ && statement_number_ == rhs.statement_number_ &&
         maybe_int_ == rhs.maybe_int_ &&
         maybe_string_ == rhs.maybe_string_;}

bool TNode::operator!=(const TNode& rhs) const { return !(rhs == *this); }
