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
                     std::unordered_set<std::shared_ptr<CFGNode>>>
      forward_map;
  std::unordered_map<std::shared_ptr<CFGNode>,
                     std::unordered_set<std::shared_ptr<CFGNode>>>
      reverse_map;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_node_map;

  auto stmt_list_children = node.GetChildren()[0]->GetChildren();
  std::vector<int> cfg_stmt_nos;
  std::shared_ptr<CFGNode> while_ptr = nullptr;

  RecursivelyTraverseAST(0, stmt_list_children, {}, while_ptr, cfg_stmt_nos,
                         forward_map, reverse_map, stmt_node_map);

  // Creation of reverse map using forward map
  for (auto& key : forward_map) {
    auto first = key.first;
    auto second = key.second;
    for (auto& s : second) {
      reverse_map[s].emplace(first);
    }
  }
  CFG cfg = CFG(proc_name, forward_map, reverse_map, stmt_node_map);
  return cfg;
}

std::vector<std::shared_ptr<CFGNode>> CFGExtractorImpl::RecursivelyTraverseAST(
    int start, std::vector<std::shared_ptr<TNode>>& children,
    std::vector<std::shared_ptr<CFGNode>> const& key_node_ptrs,
    std::shared_ptr<CFGNode>& while_ptr, std::vector<int> cfg_stmt_nos,
    std::unordered_map<std::shared_ptr<CFGNode>,
                       std::unordered_set<std::shared_ptr<CFGNode>>>&
        forward_map,
    std::unordered_map<std::shared_ptr<CFGNode>,
                       std::unordered_set<std::shared_ptr<CFGNode>>>&
        reverse_map,
    std::unordered_map<int, std::shared_ptr<CFGNode>>& stmt_node_map) const {
  auto stmt_list_size = children.size();
  for (int i = start; i < stmt_list_size; i++) {
    // Get current node in AST and statement number
    auto curr = children[i];
    int curr_stmt_no = curr->GetStatementNumber();

    // If current node is while or if
    if (curr->GetType() == TNode::While ||
        curr->GetType() == TNode::IfElseThen) {
      // Create CFGNode for While or If stmt
      auto curr_node = CFGNode({curr_stmt_no});
      auto curr_ptr = std::make_shared<CFGNode>(curr_node);

      // Add to stmt_node_map
      stmt_node_map[curr_stmt_no] = curr_ptr;

      // Create CFGNode that is before While or If and add to map(Link prev prev
      // node to prev node)
      if (!cfg_stmt_nos.empty()) {
        auto prev_ptr = std::make_shared<CFGNode>(cfg_stmt_nos);
        // Add to stmt_node_map
        for (auto& stmt_no : cfg_stmt_nos) {
          stmt_node_map[stmt_no] = prev_ptr;
        }
        // Links prev prev node to prev node if there are key_node ptrs aka prev
        // prev nodes
        if (!key_node_ptrs.empty()) {
          for (auto& key_node_ptr : key_node_ptrs) {
            forward_map[key_node_ptr].emplace(prev_ptr);
          }
        }
        // Links prev node to curr node
        forward_map[prev_ptr].emplace(curr_ptr);
      } else {
        // if there is past nodes that need linking but no stmts before it, it
        // must be a while or if node hence link prev node to curr node
        if (!key_node_ptrs.empty()) {
          for (auto& key_node_ptr : key_node_ptrs) {
            forward_map[key_node_ptr].emplace(curr_ptr);
          }
        }
      }

      // If current node is while
      if (curr->GetType() == TNode::While) {
        // Check if this while node has a parent while node
        if (while_ptr != nullptr && i == stmt_list_size - 1) {
          forward_map[curr_ptr].emplace(while_ptr);
        }
        // Goes in while children statements
        auto while_children = curr->GetChildren()[1]->GetChildren();
        auto new_while_ptr = curr_ptr;
        RecursivelyTraverseAST(0, while_children, {curr_ptr}, new_while_ptr, {},
                               forward_map, reverse_map, stmt_node_map);

        // Continue out of while if while is not the last in og stmt list
        if (i != stmt_list_size - 1) {
          start = i + 1;
          auto last_ptr =
              RecursivelyTraverseAST(start, children, {curr_ptr}, while_ptr, {},
                                     forward_map, reverse_map, stmt_node_map);
          return last_ptr;
        } else {
          std::vector<std::shared_ptr<CFGNode>> while_ptr_vector = {curr_ptr};
          return while_ptr_vector;
        }
      }

      // If current node is If
      if (curr->GetType() == TNode::IfElseThen) {
        // If there is statements after if, save while_ptr for later and unbind
        // while ptr from children
        auto after_if_while_ptr = while_ptr;
        if (i != stmt_list_size - 1) {
          while_ptr = nullptr;
        }
        // Goes in 'then' branch children statements
        auto then_children = curr->GetChildren()[1]->GetChildren();
        auto last_if_node_ptrs =
            RecursivelyTraverseAST(0, then_children, {curr_ptr}, while_ptr, {},
                                   forward_map, reverse_map, stmt_node_map);

        // Goes in 'else' branch children statements
        auto else_children = curr->GetChildren()[2]->GetChildren();
        auto last_else_node_ptrs =
            RecursivelyTraverseAST(0, else_children, {curr_ptr}, while_ptr, {},
                                   forward_map, reverse_map, stmt_node_map);

        // Combine last statement pointers for if and else branch
        std::vector<std::shared_ptr<CFGNode>> combined_ptrs = last_if_node_ptrs;
        combined_ptrs.insert(combined_ptrs.end(), last_else_node_ptrs.begin(),
                             last_else_node_ptrs.end());
        // Continue out of if and is not the last in og stmt_list
        if (i != stmt_list_size - 1) {
          start = i + 1;
          auto last_ptrs2 = RecursivelyTraverseAST(
              start, children, combined_ptrs, after_if_while_ptr, {},
              forward_map, reverse_map, stmt_node_map);
          return last_ptrs2;
        }
        return combined_ptrs;
      }
    }

    cfg_stmt_nos.emplace_back(curr_stmt_no);
    // If statement is last in stmt_list and is not while or if
    if (i == stmt_list_size - 1) {
      // Create CFGNode
      // CFGNode cfg_node = CFGNode(cfg_stmt_nos);
      auto cfg_node_ptr = std::make_shared<CFGNode>(cfg_stmt_nos);

      // Add to stmt_node_map
      for (auto& stmt_no : cfg_stmt_nos) {
        stmt_node_map[stmt_no] = cfg_node_ptr;
      }

      // link prev pointers to curr node if there is
      if (!key_node_ptrs.empty()) {
        for (auto& ptr : key_node_ptrs) {
          forward_map[ptr].emplace(cfg_node_ptr);
        }
      }
      // If under a while and is last statement, link back to while
      if (while_ptr != nullptr) {
        forward_map[cfg_node_ptr].emplace(while_ptr);
      } else {
        forward_map[cfg_node_ptr] = {};
      }
      return {cfg_node_ptr};
    }
  }
  return {nullptr};
}
