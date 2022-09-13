#include "parent_t_by_relationship.h"

ParentTByRelationship::ParentTByRelationship(int parent_t_by_statement_number)
    : parent_t_by_statement_number_(parent_t_by_statement_number) {}

void ParentTByRelationship::AddParentTStatementNumber(
    int parent_t_statement_number) {
  parent_t_statement_numbers_.emplace(parent_t_statement_number);
}

std::unordered_set<int> ParentTByRelationship::GetParentTStatementNumber()
    const {
  return parent_t_statement_numbers_;
};
