#ifndef SPA_PARENT_BY_RELATIONSHIP_H
#define SPA_PARENT_BY_RELATIONSHIP_H

#include <unordered_set>

class ParentByRelationship {
 public:
  explicit ParentByRelationship(int parent_by_statement_number);

  void AddParentStatementNumber(int parent_statement_number);

  std::unordered_set<int> GetParentStatementNumber() const;

 private:
  int parent_by_statement_number_;
  std::unordered_set<int> parent_statement_numbers_;
};

#endif  // SPA_PARENT_BY_RELATIONSHIP_H
