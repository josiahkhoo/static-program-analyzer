#ifndef SPA_RELATIONSHIP_MANAGER_H
#define SPA_RELATIONSHIP_MANAGER_H

#include <string>
#include <unordered_set>

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "follows_storage.h"

class RelationshipManager {
 public:
  RelationshipManager();
  /* ====================================
   * General Entity Adder Methods
   * ==================================== */
  // store follows to FollowsStorage
  void AddAbstraction(FollowsAbstraction abstraction);

  // store followsT to FollowsStorage
  void AddAbstraction(FollowsTAbstraction abstraction);

  std::unordered_set<std::string> GetFollowsStatements() const;

  std::unordered_set<std::string> GetFollowsCallStatements() const;

  std::unordered_set<std::string> GetFollowsReadStatements() const;

  std::unordered_set<std::string> GetFollowsPrintStatements() const;

  std::unordered_set<std::string> GetFollowsAssignStatements() const;

  std::unordered_set<std::string> GetFollowsIfStatements() const;

  std::unordered_set<std::string> GetFollowsWhileStatements() const;

  std::unordered_set<std::string> GetFollowsStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsCallStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsReadStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsPrintStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsAssignStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsIfStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsWhileStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTCallStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTReadStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTPrintStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTAssignStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTIfStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTWhileStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByStatements() const;

  std::unordered_set<std::string> GetFollowsByCallStatements() const;

  std::unordered_set<std::string> GetFollowsByReadStatements() const;

  std::unordered_set<std::string> GetFollowsByPrintStatements() const;

  std::unordered_set<std::string> GetFollowsByAssignStatements() const;

  std::unordered_set<std::string> GetFollowsByIfStatements() const;

  std::unordered_set<std::string> GetFollowsByWhileStatements() const;

  std::unordered_set<std::string> GetFollowsByCallStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByReadStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByPrintStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByAssignStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByIfStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByWhileStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByCallStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByReadStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByPrintStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByAssignStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByIfStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTByWhileStatements(
      int statement_number) const;

 private:
  static FollowsStorage followsStore;
};

#endif  // SPA_RELATIONSHIP_MANAGER_H
