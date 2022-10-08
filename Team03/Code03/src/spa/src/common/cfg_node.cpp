#include "cfg_node.h"

CFGNode::CFGNode(std::vector<int> statement_numbers)
    : statement_numbers_(std::move(statement_numbers)) {}

std::vector<int> CFGNode::GetStatementNumbers() const {
  return statement_numbers_;
}

bool CFGNode::operator==(const CFGNode& rhs) const {
  return this->statement_numbers_ == rhs.statement_numbers_;
}

bool CFGNode::operator!=(const CFGNode& rhs) const { return !(rhs == *this); }
