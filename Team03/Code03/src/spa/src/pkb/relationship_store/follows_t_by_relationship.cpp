#include "follows_t_by_relationship.h"

FollowsTByRelationship::FollowsTByRelationship(
    int follows_t_by_statement_number)
    : follows_t_by_statement_number_(follows_t_by_statement_number) {}

void FollowsTByRelationship::AddFollowsTStatementNumber(
    int follows_t_statement_number) {
  follows_t_statement_numbers_.emplace(follows_t_statement_number);
}

std::unordered_set<int> FollowsTByRelationship::GetFollowsTStatementNumber()
    const {
  return follows_t_statement_numbers_;
};
