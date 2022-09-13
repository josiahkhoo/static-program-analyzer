#ifndef SPA_PARENT_T_BY_RELATIONSHIP_H
#define SPA_PARENT_T_BY_RELATIONSHIP_H

#include <unordered_set>

class ParentTByRelationship {
 public:
  explicit ParentTByRelationship(int parent_t_by_statement_number);

  void AddParentTStatementNumber(int parent_t_statement_number);

  std::unordered_set<int> GetParentTStatementNumber() const;

 private:
  int parent_t_by_statement_number_;
  std::unordered_set<int> parent_t_statement_numbers_;
};

#endif  // SPA_PARENT_T_BY_RELATIONSHIP_H
