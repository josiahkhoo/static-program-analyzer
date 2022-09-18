#include "parent_relationship.h"

ParentRelationship::ParentRelationship(int parent_statement_number)
    : parent_statement_number_(parent_statement_number) {}

void ParentRelationship::AddParentByStatementNumber(
    int parent_by_statement_number) {
  parent_by_statement_numbers_.emplace(parent_by_statement_number);
}

std::unordered_set<int> ParentRelationship::GetParentByStatementNumbers()
    const {
  return parent_by_statement_numbers_;
}
