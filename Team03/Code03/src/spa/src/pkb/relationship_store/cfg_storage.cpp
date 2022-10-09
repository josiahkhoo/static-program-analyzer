#include "cfg_storage.h"

void CFGStorage::AddCFG(CFG cfg) {
  std::shared_ptr<CFG> cfg_ptr = std::make_shared<CFG>(cfg);
  for (auto stmt : cfg.GetStatements()) {
    stmt_to_cfg_map_[stmt] = cfg_ptr;
  }
}

/// GetStatementsProceedPath
/// \param stmt
/// \return Get all statements that have a control flow path from given stmt to
/// themselves
std::unordered_set<int> CFGStorage::GetStatementsProceedPath(int stmt) const {
  std::unordered_set<int> result;
  if (stmt_to_cfg_map_.find(stmt) != stmt_to_cfg_map_.end()) {
    for (auto s :
         stmt_to_cfg_map_.at(stmt)->GetStatementsWithinSameNode(stmt)) {
      if (s > stmt) {
        result.emplace(s);
      }
    }
    for (auto node : stmt_to_cfg_map_.at(stmt)->GetNextNodes(
             stmt_to_cfg_map_.at(stmt)->GetNode(stmt))) {
      for (auto s : node->GetStatementNumbers()) {
        result.emplace(s);
      }
    }
  }
  return result;
}

/// GetStatementsPrecedePath
/// \param stmt
/// \return Get all statements that have a control flow path from themselves to
/// given stmt
std::unordered_set<int> CFGStorage::GetStatementsPrecedePath(int stmt) const {
  std::unordered_set<int> result;
  if (stmt_to_cfg_map_.find(stmt) != stmt_to_cfg_map_.end()) {
    for (auto s :
         stmt_to_cfg_map_.at(stmt)->GetStatementsWithinSameNode(stmt)) {
      if (s < stmt) {
        result.emplace(s);
      }
    }
    for (auto node : stmt_to_cfg_map_.at(stmt)->GetPrevNodes(
             stmt_to_cfg_map_.at(stmt)->GetNode(stmt))) {
      for (auto s : node->GetStatementNumbers()) {
        result.emplace(s);
      }
    }
  }
  return result;
}

void CFGStorage::Clear() { stmt_to_cfg_map_.clear(); }