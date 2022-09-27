#ifndef SPA_PARENT_STORAGE_H
#define SPA_PARENT_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"

class ParentStorage {
 public:
  void AddRelationship(ParentAbstraction abstraction);

  void AddRelationship(ParentTAbstraction abstraction);

  std::unordered_set<std::string> GetParentStatements() const;

  std::unordered_set<std::string> GetParentStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetParentTStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetParentByStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetParentByStatements() const;

  std::unordered_set<std::string> GetParentTByStatements(
      int statement_number) const;

  // Empty storage
  void Clear();

 private:
  std::unordered_map<int, std::unordered_set<int>> parent_map_;
  std::unordered_map<int, std::unordered_set<int>> parent_by_map_;
  std::unordered_map<int, std::unordered_set<int>> parent_t_map_;
  std::unordered_map<int, std::unordered_set<int>>
      parent_t_by_map_;
};

#endif  // SPA_PARENT_STORAGE_H
