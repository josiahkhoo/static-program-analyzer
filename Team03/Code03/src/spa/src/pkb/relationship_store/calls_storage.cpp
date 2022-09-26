#include "calls_storage.h"

/// Add Calls Relationship
/// \param abstraction
void CallsStorage::AddRelationship(CallsAbstraction abstraction) {
  std::string caller = abstraction.GetLeftHandSide().GetName();
  std::string callee = abstraction.GetRightHandSide().GetName();

  if (!calls_map_.emplace(caller, std::unordered_set<std::string>{callee})
           .second) {
    calls_map_.at(caller).emplace(callee);
  }
  if (!calls_by_map_.emplace(callee, std::unordered_set<std::string>{caller})
           .second) {
    calls_by_map_.at(callee).emplace(caller);
  }
}

/// Add Calls T Relationship
/// \param abstraction
void CallsStorage::AddRelationship(CallsTAbstraction abstraction) {
  std::string caller = abstraction.GetLeftHandSide().GetName();
  std::string callee = abstraction.GetRightHandSide().GetName();

  if (!calls_t_map_.emplace(caller, std::unordered_set<std::string>{callee})
           .second) {
    calls_t_map_.at(caller).emplace(callee);
  }
  if (!calls_t_by_map_.emplace(callee, std::unordered_set<std::string>{caller})
           .second) {
    calls_t_by_map_.at(callee).emplace(caller);
  }
}

/// GetCallsProcedures
/// \return Gets all procedures that call any procedure
std::unordered_set<std::string> CallsStorage::GetCallsProcedures() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : calls_map_) {
    res.emplace(entry.first);
  }
  return res;
}

/// GetCallsProcedures
/// \param proc_name
/// \return Gets all procedures that directly call a specified procedure
std::unordered_set<std::string> CallsStorage::GetCallsProcedures(
    std::string proc_name) const {
  if (calls_by_map_.find(proc_name) == calls_by_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res = calls_by_map_.find(proc_name)->second;
  return res;
}

/// GetCallsProcedures
/// \param proc_name
/// \return Gets all procedures that directly or indirectly call a specified
/// procedure
std::unordered_set<std::string> CallsStorage::GetCallsTProcedures(
    std::string proc_name) const {
  if (calls_t_by_map_.find(proc_name) == calls_t_by_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res = calls_t_by_map_.find(proc_name)->second;
  std::unordered_set<std::string> s;
  for (std::string entry : res) {
    s.emplace(entry);
  }
  return s;
}

/// GetCallsByProcedures
/// \return Gets all procedures that are directly called by any procedure
std::unordered_set<std::string> CallsStorage::GetCallsByProcedures() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : calls_by_map_) {
    res.emplace(entry.first);
  }
  return res;
}

/// GetCallsByProcedures
/// \param proc_name
/// \return Gets all procedures that are directly called by a specified
/// procedure
std::unordered_set<std::string> CallsStorage::GetCallsByProcedures(
    std::string proc_name) const {
  if (calls_map_.find(proc_name) == calls_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res = calls_map_.find(proc_name)->second;
  return res;
}

/// GetCallsTByProcedures
/// \param proc_name
/// \return Gets all procedures that are directly or indirectly called by a
/// specified procedure
std::unordered_set<std::string> CallsStorage::GetCallsTByProcedures(
    std::string proc_name) const {
  if (calls_t_map_.find(proc_name) == calls_t_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res = calls_t_map_.find(proc_name)->second;
  return res;
}

/// Clear Storage
void CallsStorage::Clear() {
    calls_map_.clear();
    calls_by_map_.clear();
    calls_t_map_.clear();
    calls_t_by_map_.clear();

}
