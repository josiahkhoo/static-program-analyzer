#ifndef SPA_PARENT_RELATIONSHIP_H
#define SPA_PARENT_RELATIONSHIP_H

#include <unordered_set>

class ParentRelationship {
 public:
  explicit ParentRelationship(int parent_statement_number);

  void AddParentByStatementNumber(int parent_by_statement_number);

  std::unordered_set<int> GetParentByStatementNumbers() const;

 private:
  int parent_statement_number_;
  std::unordered_set<int> parent_by_statement_numbers_;
};

#endif  // SPA_PARENT_RELATIONSHIP_H
