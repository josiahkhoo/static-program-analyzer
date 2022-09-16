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
#include "uses_storage.h"

class RelationshipManager {
 public:
  /* ====================================
   * General Relationship Adder Methods
   * ==================================== */
  // store follows to FollowsStorage
  void AddAbstraction(FollowsAbstraction abstraction);

  // store followsT to FollowsStorage
  void AddAbstraction(FollowsTAbstraction abstraction);

  // store parent to ParentStorage
  void AddAbstraction(ParentAbstraction abstraction);

  // store parentT to ParentStorage
  void AddAbstraction(ParentTAbstraction abstraction);

  // store usesP to ParentStorage
  void AddAbstraction(UsesPAbstraction abstraction);

  // store usesS to ParentStorage
  void AddAbstraction(UsesSAbstraction abstraction);

  /* ====================================
   * General Relationship Getter Methods
   * ==================================== */
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

  std::unordered_set<std::string> GetUsesP() const;

  std::unordered_set<std::string> GetUsesP(std::string uses_name) const;

  std::unordered_set<std::string> GetUsesPBy() const;

  std::unordered_set<std::string> GetUsesPBy(std::string variable_name) const;

  std::unordered_set<std::string> GetUsesS() const;

  std::unordered_set<std::string> GetUsesS(std::string uses_name) const;

  std::unordered_set<std::string> GetUsesSBy() const;

  std::unordered_set<std::string> GetUsesSBy(std::string variable_name) const;

  /* ====================================
   * Clear All Relationship Storages
   * ==================================== */
  void Clear();

 private:
  FollowsStorage follows_store_;
  ParentStorage parent_store_;
  UsesStorage uses_store_;
};

#endif  // SPA_RELATIONSHIP_MANAGER_H
