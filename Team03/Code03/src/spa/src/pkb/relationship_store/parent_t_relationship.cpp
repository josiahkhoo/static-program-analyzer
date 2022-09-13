#include "parent_t_relationship.h"

ParentTRelationship::ParentTRelationship(int parent_statement_number)
    : parent_t_statement_number_(parent_statement_number) {}

void ParentTRelationship::AddParentTByStatementNumber(
    int parent_t_by_statement_number) {
  parent_t_by_statement_numbers_.emplace(parent_t_by_statement_number);
}

std::unordered_set<int> ParentTRelationship::GetParentTByStatementNumbers()
    const {
  return parent_t_by_statement_numbers_;
}
