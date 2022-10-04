#include "cfg_extractor_impl.h"

CFGExtractorImpl::CFGExtractorImpl() = default;

std::vector<CFG> CFGExtractorImpl::Extract(const TNode& ast) const {
  std::vector<CFG> cfgs;
  std::vector<std::shared_ptr<TNode>> procedures = ast.GetChildren();
  for (auto& child : procedures) {
    CFG cfg = CreateCFG(*child);
    cfgs.emplace_back(cfg);
  }

  return cfgs;
}

CFG CFGExtractorImpl::CreateCFG(const TNode& node) const {
  std::string proc_name = node.GetStringValue();
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::vector<std::shared_ptr<CFGNode>>>
      forward_map;
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::vector<std::shared_ptr<CFGNode>>>
      reverse_map;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map;
  CFG cfg = CFG(proc_name, forward_map, reverse_map, stmt_node_map);

  return cfg;
}
