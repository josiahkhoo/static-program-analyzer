#include "parent_by_relationship.h"

ParentByRelationship::ParentByRelationship(int parent_by_statement_number)
    : parent_by_statement_number_(parent_by_statement_number) {}

void ParentByRelationship::AddParentStatementNumber(
    int parent_statement_number) {
  parent_statement_numbers_.emplace(parent_statement_number);
}

std::unordered_set<int> ParentByRelationship::GetParentStatementNumber() const {
  return parent_statement_numbers_;
};
