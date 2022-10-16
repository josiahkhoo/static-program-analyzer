#ifndef SPA_RELATIONSHIP_MANAGER_H
#define SPA_RELATIONSHIP_MANAGER_H

#include <cassert>
#include <string>
#include <unordered_set>

#include "calls_storage.h"
#include "cfg_storage.h"
#include "follows_storage.h"
#include "modifies_storage.h"
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

  // store modifiesP to ModifiesStorage
  void AddAbstraction(ModifiesPAbstraction abstraction);

  // store modifiesS to ModifiesStorage
  void AddAbstraction(ModifiesSAbstraction abstraction);

  // store calls to CallsStorage
  void AddAbstraction(CallsAbstraction abstraction);

  // store callsT to CallsStorage
  void AddAbstraction(CallsTAbstraction abstraction);

  // store CFG
  void AddCFG(CFG cfg);

  /* ====================================
   * General Relationship Getter Methods
   * ==================================== */
  // Follows query methods
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

  // Parent query methods
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

  // Uses query methods
  std::unordered_set<std::string> GetUsingProcedures() const;
  std::unordered_set<std::string> GetVariablesUsedByProcedure(
      std::string procedure_name) const;
  std::unordered_set<std::string> GetVariablesUsedByProcedures() const;
  std::unordered_set<std::string> GetProceduresUsingVariable(
      std::string variable_name) const;
  std::unordered_set<std::string> GetUsingStatements() const;
  std::unordered_set<std::string> GetVariablesUsedByStatement(
      int statement_number) const;
  std::unordered_set<std::string> GetVariablesUsedByStatements() const;
  std::unordered_set<std::string> GetStatementsUsingVariable(
      std::string variable_name) const;

  // Modifies query methods
  std::unordered_set<std::string> GetModifyingProcedures() const;
  std::unordered_set<std::string> GetVariablesModifiedByProcedure(
      std::string procedure_name) const;
  std::unordered_set<std::string> GetVariablesModifiedByProcedures() const;
  std::unordered_set<std::string> GetProceduresModifyingVariable(
      std::string variable_name) const;
  std::unordered_set<std::string> GetModifyingStatements() const;
  std::unordered_set<std::string> GetVariablesModifiedByStatement(
      int statement_number) const;
  std::unordered_set<std::string> GetVariablesModifiedByStatements() const;
  std::unordered_set<std::string> GetStatementsModifyingVariable(
      std::string variable_name) const;

  // Calls query methods
  std::unordered_set<std::string> GetCallsProcedures() const;
  std::unordered_set<std::string> GetCallsProcedures(
      std::string proc_name) const;
  std::unordered_set<std::string> GetCallsTProcedures(
      std::string proc_name) const;
  std::unordered_set<std::string> GetCallsByProcedures(
      std::string proc_name) const;
  std::unordered_set<std::string> GetCallsByProcedures() const;
  std::unordered_set<std::string> GetCallsTByProcedures(
      std::string proc_name) const;

  // Next query methods
  std::unordered_set<std::string> GetAllNext() const;
  std::unordered_set<std::string> GetAllPrevious() const;
  std::unordered_set<std::string> GetNext(int statement_number) const;
  std::unordered_set<std::string> GetPrevious(int statement_number) const;
  std::unordered_set<std::string> GetNextT(int statement_number) const;
  std::unordered_set<std::string> GetPreviousT(int statement_number) const;

  // Affects query methods
  std::unordered_set<std::string> GetAllAffects(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads) const;
  std::unordered_set<std::string> GetAllAffectsBy(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads) const;
  std::unordered_set<std::string> GetAffects(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads, int statement_number) const;
  std::unordered_set<std::string> GetAffectsBy(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads, int statement_number) const;
  std::unordered_set<std::string> GetAffectsT(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads, int statement_number) const;
  std::unordered_set<std::string> GetAffectsTBy(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads, int statement_number) const;

 private:
  FollowsStorage follows_store_;
  ParentStorage parent_store_;
  UsesStorage uses_store_;
  ModifiesStorage modifies_store_;
  CallsStorage calls_store_;
  CFGStorage cfg_store_;

  void NextDFSTraversal(int statement_number,
                        std::unordered_set<int>& visited_stmts,
                        std::unordered_set<int>& nextT_stmts) const;
  void PreviousDFSTraversal(int statement_number,
                            std::unordered_set<int>& visited_stmts,
                            std::unordered_set<int>& previousT_stmts) const;
  void GetAffectsDFSTraversal(
      std::unordered_set<std::string> assigns,
      std::unordered_set<std::string> calls,
      std::unordered_set<std::string> reads, int end, int current,
      std::unordered_set<int>& cfg_visited, bool is_start,
      std::vector<int>& affecting_list,
      std::unordered_set<std::string>& relevant_vars) const;
  void GetAffectsByDFSTraversal(std::unordered_set<std::string> assigns,
                                std::unordered_set<std::string> calls,
                                std::unordered_set<std::string> reads,
                                int start, int current,
                                std::unordered_set<int>& cfg_visited,
                                bool is_start,
                                std::vector<int>& affected_list) const;
  bool IsPossibleAffects(std::unordered_set<std::string> assigns, int stmt1,
                         int stmt2) const;
  bool IsLastModifiedBroken(std::unordered_set<std::string> assigns,
                            std::unordered_set<std::string> calls,
                            std::unordered_set<std::string> reads, int current,
                            int start) const;
};

#endif  // SPA_RELATIONSHIP_MANAGER_H
