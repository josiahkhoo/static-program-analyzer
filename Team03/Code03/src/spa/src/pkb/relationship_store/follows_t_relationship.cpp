#include "follows_t_relationship.h"

FollowsTRelationship::FollowsTRelationship(int follows_statement_number)
    : follows_t_statement_number_(follows_statement_number) {}

void FollowsTRelationship::AddFollowsTByStatementNumber(
    int follows_t_by_statement_number) {
  follows_t_by_statement_numbers_.emplace(follows_t_by_statement_number);
}

std::unordered_set<int> FollowsTRelationship::GetFollowsTByStatementNumbers()
    const {
  return follows_t_by_statement_numbers_;
}
