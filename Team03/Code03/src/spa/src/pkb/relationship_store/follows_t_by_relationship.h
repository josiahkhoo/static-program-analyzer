//
// Created by Josiah Khoo on 6/9/22.
//

#ifndef SPA_FOLLOWS_T_BY_RELATIONSHIP_H
#define SPA_FOLLOWS_T_BY_RELATIONSHIP_H

#include <unordered_set>

class FollowsTByRelationship {
 public:
  explicit FollowsTByRelationship(int follows_t_by_statement_number);

  void AddFollowsTStatementNumber(int follows_t_statement_number);

  std::unordered_set<int> GetFollowsTStatementNumber() const;

 private:
  int follows_t_by_statement_number_;
  std::unordered_set<int> follows_t_statement_numbers_;
};

#endif  // SPA_FOLLOWS_T_BY_RELATIONSHIP_H
