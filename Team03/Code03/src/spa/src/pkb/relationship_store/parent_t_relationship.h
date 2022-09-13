#ifndef SPA_PARENT_T_RELATIONSHIP_H
#define SPA_PARENT_T_RELATIONSHIP_H

#include <unordered_set>

class ParentTRelationship {
 public:
  explicit ParentTRelationship(int parent_statement_number);

  void AddParentTByStatementNumber(int parent_t_by_statement_number);

  std::unordered_set<int> GetParentTByStatementNumbers() const;

 private:
  int parent_t_statement_number_;
  std::unordered_set<int> parent_t_by_statement_numbers_;
};

#endif  // SPA_PARENT_T_RELATIONSHIP_H
