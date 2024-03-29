#include "cfg.h"

#include <utility>

CFG::CFG(std::unordered_map<std::shared_ptr<CFGNode>,
                            std::unordered_set<std::shared_ptr<CFGNode>>>
             forward_map,
         std::unordered_map<std::shared_ptr<CFGNode>,
                            std::unordered_set<std::shared_ptr<CFGNode>>>
             reverse_map,
         std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map)
    : forward_map_(std::move(forward_map)),
      reverse_map_(std::move(reverse_map)),
      stmt_node_map_(std::move(stmt_node_map)) {}

std::shared_ptr<CFGNode> CFG::GetNode(int stmt_no) {
  return stmt_node_map_[stmt_no];
}

std::unordered_set<std::shared_ptr<CFGNode>> CFG::GetNextNodes(
    const std::shared_ptr<CFGNode>& cfg_node_ptr) {
  return forward_map_[cfg_node_ptr];
}

std::unordered_set<std::shared_ptr<CFGNode>> CFG::GetPrevNodes(
    const std::shared_ptr<CFGNode>& cfg_node_ptr) {
  return reverse_map_[cfg_node_ptr];
}

std::unordered_set<int> CFG::GetStatements() {
  std::unordered_set<int> statements;
  for (const auto& stmt : stmt_node_map_) {
    statements.emplace(stmt.first);
  }
  return statements;
}

std::unordered_map<std::shared_ptr<CFGNode>,
                   std::unordered_set<std::shared_ptr<CFGNode>>>
CFG::GetForwardMap() const {
  return forward_map_;
}

std::unordered_map<std::shared_ptr<CFGNode>,
                   std::unordered_set<std::shared_ptr<CFGNode>>>
CFG::GetReverseMap() const {
  return reverse_map_;
}
