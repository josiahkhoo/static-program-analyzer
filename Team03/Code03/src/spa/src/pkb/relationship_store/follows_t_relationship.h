//
// Created by Josiah Khoo on 6/9/22.
//

#ifndef SPA_FOLLOWS_T_RELATIONSHIP_H
#define SPA_FOLLOWS_T_RELATIONSHIP_H

#include <unordered_set>

class FollowsTRelationship {
 public:
  explicit FollowsTRelationship(int follows_statement_number);

  void AddFollowsTByStatementNumber(int follows_t_by_statement_number);

  std::unordered_set<int> GetFollowsTByStatementNumbers() const;

 private:
  int follows_t_statement_number_;
  std::unordered_set<int> follows_t_by_statement_numbers_;
};

#endif  // SPA_FOLLOWS_T_RELATIONSHIP_H
