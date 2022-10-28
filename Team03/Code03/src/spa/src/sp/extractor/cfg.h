#ifndef SPA_CFG_H
#define SPA_CFG_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/cfg_node.h"

class CFG {
 public:
  CFG(std::unordered_map<std::shared_ptr<CFGNode>,
                         std::unordered_set<std::shared_ptr<CFGNode>>>
          forward_map,
      std::unordered_map<std::shared_ptr<CFGNode>,
                         std::unordered_set<std::shared_ptr<CFGNode>>>
          reverse_map,
      std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map);

  [[nodiscard]] std::shared_ptr<CFGNode> GetNode(int stmt_no);

  [[nodiscard]] std::unordered_set<std::shared_ptr<CFGNode>> GetNextNodes(
      const std::shared_ptr<CFGNode>& cfg_node_ptr);

  [[nodiscard]] std::unordered_set<std::shared_ptr<CFGNode>> GetPrevNodes(
      const std::shared_ptr<CFGNode>& cfg_node_ptr);

  [[nodiscard]] std::unordered_set<int> GetStatements();

  [[nodiscard]] std::unordered_map<std::shared_ptr<CFGNode>,
                                   std::unordered_set<std::shared_ptr<CFGNode>>>
  GetForwardMap() const;
  [[nodiscard]] std::unordered_map<std::shared_ptr<CFGNode>,
                                   std::unordered_set<std::shared_ptr<CFGNode>>>
  GetReverseMap() const;

 private:
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::unordered_set<std::shared_ptr<CFGNode>>>
      forward_map_;
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::unordered_set<std::shared_ptr<CFGNode>>>
      reverse_map_;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map_;
};

#endif  // SPA_CFG_H
