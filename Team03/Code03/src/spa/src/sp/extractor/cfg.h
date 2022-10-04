#ifndef SPA_CFG_H
#define SPA_CFG_H

#include <memory>
#include <unordered_map>

#include "common/cfg_node.h"

class CFG {
 public:
  CFG(std::string proc_name,
      std::unordered_map<std::shared_ptr<CFGNode>,
                         std::vector<std::shared_ptr<CFGNode>>>
          forward_map,
      std::unordered_map<std::shared_ptr<CFGNode>,
                         std::vector<std::shared_ptr<CFGNode>>>
          reverse_map,
      std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map);

  [[nodiscard]] std::shared_ptr<CFGNode> GetNode(int stmt_no) const;

  [[nodiscard]] std::vector<std::shared_ptr<CFGNode>> GetNextNodes(
      CFGNode cfg_node) const;

  [[nodiscard]] std::vector<std::shared_ptr<CFGNode>> GetPrevNodes(
      CFGNode cfg_node) const;

  bool operator==(const CFG &rhs) const;

  bool operator!=(const CFG &rhs) const;

 private:
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::vector<std::shared_ptr<CFGNode>>>
      forward_map_;
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::vector<std::shared_ptr<CFGNode>>>
      reverse_map_;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map_;
  std::string proc_name_;
};

#endif  // SPA_CFG_H
