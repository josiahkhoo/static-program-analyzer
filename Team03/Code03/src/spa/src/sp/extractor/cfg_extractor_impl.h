#ifndef SPA_CFG_EXTRACTOR_IMPL_H
#define SPA_CFG_EXTRACTOR_IMPL_H

#include "cfg.h"
#include "cfg_extractor.h"

class CFGExtractorImpl : public CFGExtractor {
 public:
  CFGExtractorImpl();

  [[nodiscard]] std::vector<CFG> Extract(const TNode &ast) const override;

 private:
  [[nodiscard]] CFG CreateCFG(const TNode &node) const;
  std::vector<std::shared_ptr<CFGNode>> RecursivelyTraverseAST(
      int start, std::vector<std::shared_ptr<TNode>> &children,
      std::vector<std::shared_ptr<CFGNode>> const &key_node_ptrs,
      std::shared_ptr<CFGNode> &while_ptr,
      std::vector<int> cfg_stmt_nos,
      std::unordered_map<std::shared_ptr<CFGNode>,
                         std::unordered_set<std::shared_ptr<CFGNode>>>
          &forward_map,
      std::unordered_map<std::shared_ptr<CFGNode>,
                         std::unordered_set<std::shared_ptr<CFGNode>>>
          &reverse_map,
      std::unordered_map<int, std::shared_ptr<CFGNode>> &stmt_node_map) const;
};
#endif  // SPA_CFG_EXTRACTOR_IMPL_H
