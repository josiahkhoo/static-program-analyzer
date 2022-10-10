#include "cfg_node.h"

CFGNode::CFGNode(int statement_number)
    : statement_number_(std::move(statement_number)) {}

int CFGNode::GetStatementNumber() const { return statement_number_; }

bool CFGNode::operator==(const CFGNode& rhs) const {
  return this->statement_number_ == rhs.statement_number_;
}

bool CFGNode::operator!=(const CFGNode& rhs) const { return !(rhs == *this); }
