#include "relationship_manager.h"

/** ====================================
 * General Relationship Adder Methods
 * ==================================== */
/// Add Follows Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(FollowsAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
}

/// Add FollowsT Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(FollowsTAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
}

/// Add Parent Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ParentAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
}

/// Add ParentT Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ParentTAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
}

/// Add Procedure Uses Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(UsesPAbstraction abstraction) {
  uses_store_.AddRelationship(abstraction);
}

/// Add Statement Uses Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(UsesSAbstraction abstraction) {
  uses_store_.AddRelationship(abstraction);
}

/// Add Procedure Modifies Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ModifiesPAbstraction abstraction) {
  modifies_store_.AddRelationship(abstraction);
}

/// Add Statement Modifies Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ModifiesSAbstraction abstraction) {
  modifies_store_.AddRelationship(abstraction);
}

/// Add Calls Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(CallsAbstraction abstraction) {
  calls_store_.AddRelationship(abstraction);
}

/// Add Calls T Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(CallsTAbstraction abstraction) {
  calls_store_.AddRelationship(abstraction);
}

/// Add CFG
/// \param cfg
void RelationshipManager::AddCFG(CFG cfg) { cfg_store_.AddCFG(cfg); }

/** ====================================
 * General Relationship Getter Methods
 * ==================================== */
/// GetFollowsStatements
/// \return Gets all statements following any statement
std::unordered_set<std::string> RelationshipManager::GetFollowsStatements()
    const {
  return follows_store_.GetFollowsStatements();
}

/// GetFollowsStatements
/// \param statement_number
/// \return Gets all statements directly following a specified statement
std::unordered_set<std::string> RelationshipManager::GetFollowsStatements(
    int statement_number) const {
  return follows_store_.GetFollowsStatements(statement_number);
}

/// GetFollowsTStatements
/// \param statement_number
/// \return Gets all statements directly or indirectly following a specified
/// statement
std::unordered_set<std::string> RelationshipManager::GetFollowsTStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTStatements(statement_number);
}

/// GetFollowsByStatements
/// \param statement_number
/// \return Gets all statements directly followed by a specified statement
std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsByStatements(statement_number);
}

/// GetFollowsByStatements
/// \return Gets all statements followed by any statement
std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements()
    const {
  return follows_store_.GetFollowsByStatements();
}

/// GetFollowsTByStatements
/// \param statement_number
/// \return Gets all statements directly or indirectly followed by a specified
/// statement
std::unordered_set<std::string> RelationshipManager::GetFollowsTByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTByStatements(statement_number);
}

/// GetParentStatements
/// \return Gets all statements that are direct parents of any statement
std::unordered_set<std::string> RelationshipManager::GetParentStatements()
    const {
  return parent_store_.GetParentStatements();
}

/// GetParentStatements
/// \param statement_number
/// \return Gets all statements that are direct parents of a specified statement
std::unordered_set<std::string> RelationshipManager::GetParentStatements(
    int statement_number) const {
  return parent_store_.GetParentStatements(statement_number);
}

/// GetParentTStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect parents of a
/// specified statement
std::unordered_set<std::string> RelationshipManager::GetParentTStatements(
    int statement_number) const {
  return parent_store_.GetParentTStatements(statement_number);
}

/// GetParentByStatements
/// \param statement_number
/// \return Gets all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> RelationshipManager::GetParentByStatements(
    int statement_number) const {
  return parent_store_.GetParentByStatements(statement_number);
}

/// GetParentByStatements
/// \return Gets all statements that are direct children of any statement
std::unordered_set<std::string> RelationshipManager::GetParentByStatements()
    const {
  return parent_store_.GetParentByStatements();
}

/// GetParentTByStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> RelationshipManager::GetParentTByStatements(
    int statement_number) const {
  return parent_store_.GetParentTByStatements(statement_number);
}

/// GetUsingProcedures
/// \return Gets all procedures that use variables
std::unordered_set<std::string> RelationshipManager::GetUsingProcedures()
    const {
  return uses_store_.GetUsingProcedures();
}

/// GetVariablesUsedByProcedure
/// \param procedure_name
/// \return Gets all variables used by a specified procedure
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByProcedure(
    std::string procedure_name) const {
  return uses_store_.GetVariablesUsedByProcedure(procedure_name);
}

/// GetVariablesUsedByProcedures
/// \return Gets all variables that are used by procedures
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByProcedures() const {
  return uses_store_.GetVariablesUsedByProcedures();
}

/// GetProceduresUsingVariable
/// \param variable_name
/// \return Gets all procedures that use a specified variable
std::unordered_set<std::string> RelationshipManager::GetProceduresUsingVariable(
    std::string variable_name) const {
  return uses_store_.GetProceduresUsingVariable(variable_name);
}

/// GetUsingStatements
/// \return Gets all statements that use variables
std::unordered_set<std::string> RelationshipManager::GetUsingStatements()
    const {
  return uses_store_.GetUsingStatements();
}

/// GetVariablesUsedByStatement
/// \param statement_number
/// \return Gets all variables used by a specified statement
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByStatement(int statement_number) const {
  return uses_store_.GetVariablesUsedByStatement(statement_number);
}

/// GetVariablesUsedByStatements
/// \return Gets all variables that are used by statements
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByStatements() const {
  return uses_store_.GetVariablesUsedByStatements();
}

/// GetStatementsUsingVariable
/// \param variable_name
/// \return Gets all statements that use a specified variable
std::unordered_set<std::string> RelationshipManager::GetStatementsUsingVariable(
    std::string variable_name) const {
  return uses_store_.GetStatementsUsingVariable(variable_name);
}

/// GetModifyingProcedures
/// \return Gets all procedures that modify variables
std::unordered_set<std::string> RelationshipManager::GetModifyingProcedures()
    const {
  return modifies_store_.GetModifyingProcedures();
}

/// GetVariablesModifiedByProcedure
/// \param procedure_name
/// \return Gets all variables modified by a specified procedure
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByProcedure(
    std::string procedure_name) const {
  return modifies_store_.GetVariablesModifiedByProcedure(procedure_name);
}

/// GetVariablesModifiedByProcedures
/// \return Gets all variables that are modified by procedures
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByProcedures() const {
  return modifies_store_.GetVariablesModifiedByProcedures();
}

/// GetProceduresModifyingVariable
/// \param variable_name
/// \return Gets all procedures that modify a specified variable
std::unordered_set<std::string>
RelationshipManager::GetProceduresModifyingVariable(
    std::string variable_name) const {
  return modifies_store_.GetProceduresModifyingVariable(variable_name);
}

/// GetModifyingStatements
/// \return Gets all statements that modify variables
std::unordered_set<std::string> RelationshipManager::GetModifyingStatements()
    const {
  return modifies_store_.GetModifyingStatements();
}

/// GetVariablesModifiedByStatement
/// \param statement_number
/// \return Gets all variables modified by a specified statement
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByStatement(
    int statement_number) const {
  return modifies_store_.GetVariablesModifiedByStatement(statement_number);
}

/// GetVariablesModifiedByStatements
/// \return Gets all variables that are modified by statements
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByStatements() const {
  return modifies_store_.GetVariablesModifiedByStatements();
}

/// GetStatementsModifyingVariable
/// \param variable_name
/// \return Gets all statements that modify a specified variable
std::unordered_set<std::string>
RelationshipManager::GetStatementsModifyingVariable(
    std::string variable_name) const {
  return modifies_store_.GetStatementsModifyingVariable(variable_name);
}

/// GetCallsProcedures
/// \return Gets all procedures that call any procedure
std::unordered_set<std::string> RelationshipManager::GetCallsProcedures()
    const {
  return calls_store_.GetCallsProcedures();
}

/// GetCallsProcedures
/// \param proc_name
/// \return Gets all procedures that directly call a specified procedure
std::unordered_set<std::string> RelationshipManager::GetCallsProcedures(
    std::string proc_name) const {
  return calls_store_.GetCallsProcedures(proc_name);
}

/// GetCallsProcedures
/// \param proc_name
/// \return Gets all procedures that directly or indirectly call a specified
/// procedure
std::unordered_set<std::string> RelationshipManager::GetCallsTProcedures(
    std::string proc_name) const {
  return calls_store_.GetCallsTProcedures(proc_name);
}

/// GetCallsByProcedures
/// \return Gets all procedures that are directly called by any procedure
std::unordered_set<std::string> RelationshipManager::GetCallsByProcedures()
    const {
  return calls_store_.GetCallsByProcedures();
}

/// GetCallsByProcedures
/// \param proc_name
/// \return Gets all procedures that are directly called by a specified
/// procedure
std::unordered_set<std::string> RelationshipManager::GetCallsByProcedures(
    std::string proc_name) const {
  return calls_store_.GetCallsByProcedures(proc_name);
}

/// GetCallsTByProcedures
/// \param proc_name
/// \return Gets all procedures that are directly or indirectly called by a
/// specified procedure
std::unordered_set<std::string> RelationshipManager::GetCallsTByProcedures(
    std::string proc_name) const {
  return calls_store_.GetCallsTByProcedures(proc_name);
}

/// GetAllNext
/// \return Query all statements that come next to some statement
std::unordered_set<std::string> RelationshipManager::GetAllNext() const {
  return {};
}

/// GetAllPrevious
/// \return Query all statements that come previous to some statement
std::unordered_set<std::string> RelationshipManager::GetAllPrevious() const {
  return {};
}

/// GetNext
/// \param statement_number statement
/// \return Query statement(s) that comes next after given statement
std::unordered_set<std::string> RelationshipManager::GetNext(
    int statement_number) const {
  assert(statement_number);
  return {};
}

/// GetPrevious
/// \param statement_number statement
/// \return Query statement(s) that comes previous before given statement
std::unordered_set<std::string> RelationshipManager::GetPrevious(
    int statement_number) const {
  assert(statement_number);
  return {};
}

/// GetNextT
/// \param statement_number statement
/// \return Query statement(s) that comes nextT after given statement
std::unordered_set<std::string> RelationshipManager::GetNextT(
    int statement_number) const {
  std::unordered_set<int> visited_stmts;
  std::unordered_set<int> nextT_stmts;
  NextDFSTraversal(statement_number, visited_stmts, nextT_stmts);

  std::unordered_set<std::string> result;
  for (auto s : nextT_stmts) {
    result.emplace(std::to_string(s));
  }
  return result;
}

/// GetPreviousT
/// \param statement_number statement
/// \return Query statement(s) that comes previousT before given statement
std::unordered_set<std::string> RelationshipManager::GetPreviousT(
    int statement_number) const {
  std::unordered_set<int> visited_stmts;
  std::unordered_set<int> previousT_stmts;
  PreviousDFSTraversal(statement_number, visited_stmts, previousT_stmts);

  std::unordered_set<std::string> result;
  for (auto s : previousT_stmts) {
    result.emplace(std::to_string(s));
  }
  return result;
}

/// GetAllAffects
/// \return Query all assign statements that affects some other statement
/// Get set of s such that Affects(s, _)
std::unordered_set<std::string> RelationshipManager::GetAllAffects(
    std::unordered_set<std::string> assigns) const {
  std::unordered_set<std::string> result;
  for (auto stmt : assigns) {
    std::unordered_set<std::string> stmts_affecting =
        GetAffects(assigns, std::stoi(stmt));
    if (!stmts_affecting.empty()) {
      for (auto s : stmts_affecting) {
        result.emplace(s);
      }
    }
  }
  return result;
}

/// GetAllAffectsBy
/// \return Query all assign statements that are affected by some other
/// statement
/// Get set of s such that Affects(_, s)
std::unordered_set<std::string> RelationshipManager::GetAllAffectsBy(
    std::unordered_set<std::string> assigns) const {
  std::unordered_set<std::string> result;
  for (auto stmt : assigns) {
    std::unordered_set<std::string> stmts_affected =
        GetAffectsBy(assigns, std::stoi(stmt));
    if (!stmts_affected.empty()) {
      for (auto s : stmts_affected) {
        result.emplace(s);
      }
    }
  }
  return result;
}

/// GetAffects
/// \param statement_number statement
/// \return Query all assign statements that affects given statement
/// Get set of s such that Affects(s, statement)
std::unordered_set<std::string> RelationshipManager::GetAffects(
    std::unordered_set<std::string> assigns, int statement_number) const {
  std::unordered_set<int> cfg_path;
  std::vector<int> affecting_list;
  std::unordered_set<std::string> modified_list;

  if (assigns.find(std::to_string(statement_number)) != assigns.end()) {
    GetAffectsDFSTraversal(assigns, statement_number, statement_number,
                           cfg_path, true, affecting_list, modified_list);
  }

  std::unordered_set<std::string> result;
  for (auto s : affecting_list) {
    result.emplace(std::to_string(s));
  }
  return result;
}

/// GetAffectsBy
/// \param statement_number statement
/// \return Query all assign statements that are affected by given statement
/// /// Get set of s such that Affects(statement, s)
std::unordered_set<std::string> RelationshipManager::GetAffectsBy(
    std::unordered_set<std::string> assigns, int statement_number) const {
  std::unordered_set<int> cfg_path;
  std::vector<int> affected_list;

  if (assigns.find(std::to_string(statement_number)) != assigns.end()) {
    GetAffectsByDFSTraversal(assigns, statement_number, statement_number,
                             cfg_path, true, affected_list);
  }

  std::unordered_set<std::string> result;
  for (auto s : affected_list) {
    result.emplace(std::to_string(s));
  }
  return result;
}

/// GetAffectsT
/// \param statement_number statement
/// \return Query all assign statements that affectsT given statement
std::unordered_set<std::string> RelationshipManager::GetAffectsT(
    std::unordered_set<std::string> assigns, int statement_number) const {
  assert(statement_number);
  return assigns;
}

/// GetAffectsTBy
/// \param statement_number statement
/// \return Query all assign statements that are affectedT by given statement
std::unordered_set<std::string> RelationshipManager::GetAffectsTBy(
    std::unordered_set<std::string> assigns, int statement_number) const {
  assert(statement_number);
  return assigns;
}

/// Clear Storage
void RelationshipManager::Clear() {
  follows_store_.Clear();
  parent_store_.Clear();
  uses_store_.Clear();
  modifies_store_.Clear();
  calls_store_.Clear();
}

void RelationshipManager::NextDFSTraversal(
    int statement_number, std::unordered_set<int> &visited_stmts,
    std::unordered_set<int> &nextT_stmts) const {
  // Add current statement to visited
  visited_stmts.emplace(statement_number);
  // Retrieve forward neighbouring stmts of current stmt node
  std::unordered_set<int> neighbouring_stmts =
      cfg_store_.GetForwardNeighbours(statement_number);

  for (auto stmt : neighbouring_stmts) {
    if (nextT_stmts.find(stmt) == nextT_stmts.end()) {
      nextT_stmts.emplace(stmt);
    }
    // Visit unvisited nodes
    if (visited_stmts.find(stmt) == visited_stmts.end()) {
      NextDFSTraversal(stmt, visited_stmts, nextT_stmts);
    }
  }
}

void RelationshipManager::PreviousDFSTraversal(
    int statement_number, std::unordered_set<int> &visited_stmts,
    std::unordered_set<int> &previousT_stmts) const {
  // Add current statement to visited
  visited_stmts.emplace(statement_number);
  // Retrieve backward neighbouring stmts of current stmt node
  std::unordered_set<int> neighbouring_stmts =
      cfg_store_.GetBackwardNeighbours(statement_number);

  for (auto stmt : neighbouring_stmts) {
    if (previousT_stmts.find(stmt) == previousT_stmts.end()) {
      previousT_stmts.emplace(stmt);
    }
    // Visit unvisited nodes
    if (visited_stmts.find(stmt) == visited_stmts.end()) {
      PreviousDFSTraversal(stmt, visited_stmts, previousT_stmts);
    }
  }
}

void RelationshipManager::GetAffectsDFSTraversal(
    std::unordered_set<std::string> assigns, int end, int current,
    std::unordered_set<int> &cfg_path, bool is_start,
    std::vector<int> &affecting_list,
    std::unordered_set<std::string> &relevant_vars) const {
  std::unordered_set<std::string> used_vars = GetVariablesUsedByStatement(end);
  std::unordered_set<std::string> relevant_modified_vars;
  std::unordered_set<std::string> modified_vars;

  // Not root node
  if (!is_start) {
    // Get vars that are modified by current stmt
    modified_vars = GetVariablesModifiedByStatement(current);
    for (auto var : modified_vars) {
      // Check if var modified are not modified later on
      if (relevant_vars.find(var) == relevant_vars.end()) {
        // Check if var modified is used in end
        if (used_vars.find(var) != used_vars.end()) {
          // Check current is an assign statement
          if (assigns.find(std::to_string(current)) != assigns.end()) {
            affecting_list.push_back(current);
          }
          relevant_vars.emplace(var);
          relevant_modified_vars.emplace(var);
        }
      }
    }
  }

  // Early return if variables used by end are all modified along the way
  if (used_vars == relevant_vars) {
    for (auto var : relevant_modified_vars) {
      relevant_vars.erase(var);
    }
    return;
  }

  // Add stmt to cfg path if it is not root of DFS
  if (!is_start) {
    cfg_path.emplace(current);
  }

  // Loop through previous neighbouring stmts
  for (auto neighbour_stmt : cfg_store_.GetBackwardNeighbours(current)) {
    // Neighbour has not been visited
    if (cfg_path.find(neighbour_stmt) == cfg_path.end()) {
      GetAffectsDFSTraversal(assigns, end, neighbour_stmt, cfg_path, false,
                             affecting_list, relevant_vars);
    }
  }

  for (auto var : relevant_modified_vars) {
    relevant_vars.erase(var);
  }
  cfg_path.erase(current);
  return;
}

void RelationshipManager::GetAffectsByDFSTraversal(
    std::unordered_set<std::string> assigns, int start, int current,
    std::unordered_set<int> &cfg_path, bool is_start,
    std::vector<int> &affected_list) const {
  if (!is_start) {
    if (IsPossibleAffects(assigns, start, current)) {
      affected_list.push_back(current);
    }
    if (IsLastModifiedBroken(current, start)) {
      return;
    }
  }

  if (!is_start) {
    cfg_path.emplace(current);
  }

  // Loop through forward neighbouring stmts
  for (auto neighbour_stmt : cfg_store_.GetForwardNeighbours(current)) {
    // Neighbour has not been visited
    if (cfg_path.find(neighbour_stmt) != cfg_path.end()) {
      GetAffectsByDFSTraversal(assigns, start, neighbour_stmt, cfg_path, false,
                               affected_list);
    }
  }
  return;
}

bool RelationshipManager::IsPossibleAffects(
    std::unordered_set<std::string> assigns, int stmt1, int stmt2) const {
  if (assigns.find(std::to_string(stmt1)) == assigns.end()) {
    return false;
  }
  if (assigns.find(std::to_string(stmt2)) == assigns.end()) {
    return false;
  }
  std::unordered_set<std::string> modified_vars_in_stmt1 =
      GetVariablesModifiedByStatement(stmt1);
  std::unordered_set<std::string> used_vars_in_stmt2 =
      GetVariablesUsedByStatement(stmt2);
  for (auto s : modified_vars_in_stmt1) {
    if (used_vars_in_stmt2.find(s) != used_vars_in_stmt2.end()) {
      return true;
    }
  }
  return false;
}

bool RelationshipManager::IsLastModifiedBroken(int current, int start) const {
  std::unordered_set<std::string> modified_vars_in_start =
      GetVariablesModifiedByStatement(start);
  std::unordered_set<std::string> modified_vars_in_current =
      GetVariablesModifiedByStatement(current);
  for (auto s : modified_vars_in_start) {
    if (modified_vars_in_current.find(s) != modified_vars_in_current.end()) {
      return true;
    }
  }
  return false;
}
