#ifndef SPA_NEXT_STORAGE_H
#define SPA_NEXT_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/abstraction/next_abstraction.h"

class NextStorage {
 public:
  void AddRelationship(NextAbstraction abstraction);

  std::unordered_set<std::string> GetPreviousStatements() const;

  std::unordered_set<std::string> GetNextStatements() const;

  std::unordered_set<std::string> GetPreviousStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetNextStatements(int statement_number) const;

  // Empty storage
  void Clear();

 private:
  std::unordered_map<int, std::unordered_set<int>> previous_to_next_map_;
  std::unordered_map<int, std::unordered_set<int>> next_to_previous_map_;
};

#endif  // SPA_NEXT_STORAGE_H
