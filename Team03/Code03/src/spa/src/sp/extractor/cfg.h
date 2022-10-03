#ifndef SPA_CFG_H
#define SPA_CFG_H

#include <memory>
#include <unordered_map>

#include "common/cfg_node.h"

class CFG {
 public:
  CFG (std::unordered_map<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>> forward_map,
      std::unordered_map<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>> reverse_map,
      std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map);

  std::shared_ptr<CFGNode> GetNode(int stmt_no);

  std::shared_ptr<CFGNode> GetNextNode(CFGNode cfg_node);

  std::shared_ptr<CFGNode> GetPrevNode(CFGNode cfg_node);

  bool operator==(const CFG &rhs) const;

  bool operator!=(const CFG &rhs) const;
 private:
  std::unordered_map<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>> forward_map_;
  std::unordered_map<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>> reverse_map_;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map_;
};

#endif  // SPA_CFG_H
