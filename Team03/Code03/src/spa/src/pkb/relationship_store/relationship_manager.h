#ifndef SPA_RELATIONSHIP_MANAGER_H
#define SPA_RELATIONSHIP_MANAGER_H

#include <string>
#include <unordered_set>

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"
#include "follows_storage.h"
#include "parent_storage.h"

class RelationshipManager {
 public:
  /* ====================================
   * General Entity Adder Methods
   * ==================================== */
  // store follows to FollowsStorage
  void AddAbstraction(FollowsAbstraction abstraction);

  // store followsT to FollowsStorage
  void AddAbstraction(FollowsTAbstraction abstraction);

  // store parent to ParentStorage
  void AddAbstraction(ParentAbstraction abstraction);

  // store parentT to ParentStorage
  void AddAbstraction(ParentTAbstraction abstraction);

  std::unordered_set<std::string> GetFollowsStatements() const;

  std::unordered_set<std::string> GetFollowsStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByStatements() const;

  std::unordered_set<std::string> GetFollowsTByStatements(
      int statement_number) const;

 private:
  FollowsStorage follows_store;
  ParentStorage parent_store;
};

#endif  // SPA_RELATIONSHIP_MANAGER_H
