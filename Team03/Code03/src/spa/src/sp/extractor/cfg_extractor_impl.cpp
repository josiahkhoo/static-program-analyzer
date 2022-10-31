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
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::unordered_set<std::shared_ptr<CFGNode>>>
      forward_map;
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::unordered_set<std::shared_ptr<CFGNode>>>
      reverse_map;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map;

  auto stmt_list_children = node.GetChildren()[0]->GetChildren();
  std::vector<int> cfg_stmt_nos;
  std::shared_ptr<CFGNode> while_ptr = nullptr;

  RecursivelyTraverseAST(0, stmt_list_children, {}, while_ptr, forward_map,
                         reverse_map, stmt_node_map);

  // Creation of reverse map using forward map
  for (auto& key : forward_map) {
    auto first = key.first;
    auto second = key.second;
    for (auto& s : second) {
      reverse_map[s].emplace(first);
    }
  }
  CFG cfg = CFG(forward_map, reverse_map, stmt_node_map);
  return cfg;
}

std::vector<std::shared_ptr<CFGNode>> CFGExtractorImpl::RecursivelyTraverseAST(
    int start, std::vector<std::shared_ptr<TNode>>& children,
    std::vector<std::shared_ptr<CFGNode>> const& key_node_ptrs,
    std::shared_ptr<CFGNode>& while_ptr,
    std::unordered_map<std::shared_ptr<CFGNode>,
                       std::unordered_set<std::shared_ptr<CFGNode>>>&
        forward_map,
    std::unordered_map<std::shared_ptr<CFGNode>,
                       std::unordered_set<std::shared_ptr<CFGNode>>>&
        reverse_map,
    std::unordered_map<int, std::shared_ptr<CFGNode>>& stmt_node_map) const {
  auto stmt_list_size = children.size();
  auto parent_ptrs = key_node_ptrs;
  for (int i = start; i < (int)stmt_list_size; i++) {
    // Get current node in AST and statement number and create a node for it
    auto curr = children[i];
    int curr_stmt_no = curr->GetStatementNumber();
    auto curr_node_ptr = std::make_shared<CFGNode>(curr_stmt_no);
    stmt_node_map[curr_stmt_no] = curr_node_ptr;

    // If there are parent nodes, link them to curr node
    if (!parent_ptrs.empty()) {
      for (auto& ptr : parent_ptrs) {
        forward_map[ptr].emplace(curr_node_ptr);
      }
    }
    // If current node is while
    if (curr->GetType() == TNode::While) {
      // Check if this while node has a parent while node
      if (while_ptr != nullptr && i == (int)stmt_list_size - 1) {
        forward_map[curr_node_ptr].emplace(while_ptr);
      }
      // Goes in while children statements
      auto while_children = curr->GetChildren()[1]->GetChildren();
      auto new_while_ptr = curr_node_ptr;
      RecursivelyTraverseAST(0, while_children, {curr_node_ptr}, new_while_ptr,
                             forward_map, reverse_map, stmt_node_map);

      // Continue out of while if while is not the last in og stmt list
      if (i != (int)stmt_list_size - 1) {
        start = i + 1;
        auto last_ptr =
            RecursivelyTraverseAST(start, children, {curr_node_ptr}, while_ptr,
                                   forward_map, reverse_map, stmt_node_map);
        return last_ptr;
      } else {
        std::vector<std::shared_ptr<CFGNode>> while_ptr_vector = {
            curr_node_ptr};
        return while_ptr_vector;
      }
    }
    // If current node is If
    if (curr->GetType() == TNode::IfElseThen) {
      // If there is statements after if, save while_ptr for later and unbind
      // while ptr from children
      auto after_if_while_ptr = while_ptr;
      if (i != (int)stmt_list_size - 1) {
        while_ptr = nullptr;
      }
      // Goes in 'then' branch children statements
      auto then_children = curr->GetChildren()[1]->GetChildren();
      auto last_if_node_ptrs =
          RecursivelyTraverseAST(0, then_children, {curr_node_ptr}, while_ptr,
                                 forward_map, reverse_map, stmt_node_map);

      // Goes in 'else' branch children statements
      auto else_children = curr->GetChildren()[2]->GetChildren();
      auto last_else_node_ptrs =
          RecursivelyTraverseAST(0, else_children, {curr_node_ptr}, while_ptr,
                                 forward_map, reverse_map, stmt_node_map);

      // Combine last statement pointers for if and else branch
      std::vector<std::shared_ptr<CFGNode>> combined_ptrs = last_if_node_ptrs;
      combined_ptrs.insert(combined_ptrs.end(), last_else_node_ptrs.begin(),
                           last_else_node_ptrs.end());
      // Continue out of if and is not the last in og stmt_list
      if (i != (int)stmt_list_size - 1) {
        start = i + 1;
        auto last_ptrs2 = RecursivelyTraverseAST(
            start, children, combined_ptrs, after_if_while_ptr, forward_map,
            reverse_map, stmt_node_map);
        return last_ptrs2;
      }
      return combined_ptrs;
    }
    // Replace parent ptr to curr ptr
    parent_ptrs = {curr_node_ptr};
    // If statement is last in stmt_list and is not while or if
    if (i == (int)stmt_list_size - 1) {
      // If under a while and is last statement, link back to while
      if (while_ptr != nullptr) {
        forward_map[curr_node_ptr].emplace(while_ptr);
      } else {
        forward_map[curr_node_ptr] = {};
      }
      return {curr_node_ptr};
    }
  }
  return {nullptr};
}