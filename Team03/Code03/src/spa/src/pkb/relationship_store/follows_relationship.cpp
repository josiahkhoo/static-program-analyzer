#include "follows_relationship.h"

FollowsRelationship::FollowsRelationship(int follows_statement_number_, int follow_by_statement_number_) {};

int FollowsRelationship::GetFollows() const {
  return follows_statement_number_;
}

int FollowsRelationship::GetFollowBy() const {
  return follow_by_statement_number_;
}

//Need to string methods?
