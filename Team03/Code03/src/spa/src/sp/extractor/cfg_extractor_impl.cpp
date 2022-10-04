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

  auto stmt_list_children = node.GetChildren()[0]->GetChildren();
  auto stmt_list_size = stmt_list_children.size();
  auto curr = stmt_list_children[0];
  std::vector<int> cfg_stmt_nos;
  for (int i = 0; i < stmt_list_size; i++) {
    if (i == stmt_list_size - 1) {
      // Last in stmt_list
      cfg_stmt_nos.emplace_back(curr->GetStatementNumber());

    }
  }

  CFG cfg = CFG(proc_name, forward_map, reverse_map, stmt_node_map);
  return cfg;
}
