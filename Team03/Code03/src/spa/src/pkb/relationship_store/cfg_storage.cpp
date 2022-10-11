#include "cfg_storage.h"

void CFGStorage::AddCFG(CFG cfg) {
  std::shared_ptr<CFG> cfg_ptr = std::make_shared<CFG>(cfg);
  cfg_set.emplace(cfg_ptr);
  for (auto stmt : cfg.GetStatements()) {
    stmt_to_cfg_map_[stmt] = cfg_ptr;
  }
}

std::unordered_set<std::shared_ptr<CFG>> CFGStorage::GetCfgSet() const {
  return cfg_set;
}

/// GetForwardNeighbours
/// \param stmt
/// \return Get forward neighbouring stmts of given stmt
std::unordered_set<int> CFGStorage::GetForwardNeighbours(int stmt) const {
  std::unordered_set<int> result;
  if (stmt_to_cfg_map_.find(stmt) != stmt_to_cfg_map_.end()) {
    for (auto node : stmt_to_cfg_map_.at(stmt)->GetNextNodes(
             stmt_to_cfg_map_.at(stmt)->GetNode(stmt))) {
      result.emplace(node->GetStatementNumber());
    }
  }
  return result;
}

/// GetBackwardNeighbours
/// \param stmt
/// \return Get backward neighbouring stmts of given stmt
std::unordered_set<int> CFGStorage::GetBackwardNeighbours(int stmt) const {
  std::unordered_set<int> result;
  if (stmt_to_cfg_map_.find(stmt) != stmt_to_cfg_map_.end()) {
    for (auto node : stmt_to_cfg_map_.at(stmt)->GetPrevNodes(
             stmt_to_cfg_map_.at(stmt)->GetNode(stmt))) {
      result.emplace(node->GetStatementNumber());
    }
  }
  return result;
}

void CFGStorage::Clear() { stmt_to_cfg_map_.clear(); }