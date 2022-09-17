#include "planner.h"

#include <unordered_map>

#include "qps/qnodes/abstraction_node.h"
#include "qps/qnodes/boolean_node.h"
#include "qps/qnodes/entity_node.h"
#include "qps/qnodes/intersect_node.h"
#include "qps/qnodes/join_node.h"
#include "query_string.h"

Planner::Planner() = default;

std::shared_ptr<QNode> Planner::Plan(const QueryString &q_string) const {
  Select select_clause = q_string.GetSelect();
  std::vector<std::shared_ptr<QueryOperation>> no_syn_ops, single_syn_ops,
      double_syn_ops;

  // Separate into respective operations
  for (const auto &ops : q_string.GetQueryOperation()) {
    switch (ops->GetType()) {
      case (QueryOperation::NO_SYNONYM):
        no_syn_ops.push_back(ops);
        break;
      case (QueryOperation::SINGLE_SYNONYM):
        single_syn_ops.push_back(ops);
        break;
      case (QueryOperation::DOUBLE_SYNONYM):
        double_syn_ops.push_back(ops);
        break;
      default:
        assert(false);
    }
  }

  std::vector<std::shared_ptr<QNode>> abstraction_nodes;
  std::unordered_map<std::shared_ptr<QNode>, std::shared_ptr<QueryOperation>>
      abstraction_node_to_query_op_map;

  // Create join nodes
  for (const auto &double_syn_op : double_syn_ops) {
    // Find all relevant single syn ops
    std::vector<std::shared_ptr<QueryOperation>> lhs_single_syn_ops,
        rhs_single_syn_ops;
    auto [lhs_syn, rhs_syn] = double_syn_op->GetSynonymPair();
    for (const auto &single_syn_op : single_syn_ops) {
      if (single_syn_op->GetSynonym() == lhs_syn) {
        // Find if LHS has single syn op
        lhs_single_syn_ops.push_back(single_syn_op);
      } else if (single_syn_op->GetSynonym() == rhs_syn) {
        // Find if RHS has single syn op
        rhs_single_syn_ops.push_back(single_syn_op);
      }
    }

    // Add single syn ops if either one is empty
    std::shared_ptr<QNode> lhs_node, rhs_node;
    if (lhs_single_syn_ops.empty()) {
      lhs_node = std::make_shared<EntityNode>(lhs_syn);
    } else {
      lhs_node = BuildIntersectTree(lhs_single_syn_ops);
    }
    if (rhs_single_syn_ops.empty()) {
      rhs_node = std::make_shared<EntityNode>(rhs_syn);
    } else {
      rhs_node = BuildIntersectTree(rhs_single_syn_ops);
    }

    // Create an abstraction node WITH children
    auto abstraction_node = std::make_shared<AbstractionNode>(double_syn_op);
    abstraction_node->SetLeftNode(lhs_node);
    abstraction_node->SetRightNode(rhs_node);

    // Add to list of abstraction nodes
    abstraction_nodes.push_back(abstraction_node);
    // Add to abstraction node -> query operator map
    abstraction_node_to_query_op_map[abstraction_node] = double_syn_op;
  }

  // Assemble abstraction nodes
  std::unordered_set<std::shared_ptr<QNode>> seen;
  std::unordered_set<std::shared_ptr<QNode>> disjoint_join_nodes;
  for (const auto &node1 : abstraction_nodes) {
    if (seen.find(node1) == seen.end()) {
      std::shared_ptr<QNode> current_node = node1;
      seen.insert(node1);
      // If node not seen yet link with other relevant nodes
      std::shared_ptr<QueryOperation> node1_op =
          abstraction_node_to_query_op_map[node1];
      for (const auto &node2 : abstraction_nodes) {
        std::shared_ptr<QueryOperation> node2_op =
            abstraction_node_to_query_op_map[node2];
        // Check if in seen
        if (seen.find(node2) == seen.end()) {
          // If not seen compare node1_op if its common with node2_op
          if (node1_op->GetSynonymPair().first ==
                  node2_op->GetSynonymPair().first ||
              node1_op->GetSynonymPair().first ==
                  node2_op->GetSynonymPair().second ||
              node1_op->GetSynonymPair().second ==
                  node2_op->GetSynonymPair().first ||
              node1_op->GetSynonymPair().second ==
                  node2_op->GetSynonymPair().second) {
          }
          // Make current node left hand child of new node
          // and make node 2 right hand child of new node,
          // then swap new node and current node
          auto new_node = std::make_shared<JoinNode>();
          new_node->SetLeftNode(current_node);
          new_node->SetRightNode(node2);
          current_node = new_node;
        }
      }
      // Add current node to disjoint join nodes after iteration
      disjoint_join_nodes.emplace(current_node);
    }
  }

  // Combine disjoint join nodes via join operation
  std::shared_ptr<QNode> head = std::make_shared<QNode>();
  for (const auto &node : disjoint_join_nodes) {
    auto new_head = std::make_shared<JoinNode>();
    new_head->SetLeftNode(head);
    new_head->SetRightNode(node);
    head = new_head;
  }

  // Add all unused synonyms to RHS of the top node
  for (const auto &syn : q_string.GetSynonyms()) {
    bool used = false;
    for (const auto &double_syn_op : double_syn_ops) {
      if (syn == double_syn_op->GetSynonymPair().first ||
          syn == double_syn_op->GetSynonymPair().second) {
        used = true;
        break;
      }
    }
    if (used) {
      // Skip if synonym is used before
      continue;
    }
    std::vector<std::shared_ptr<QueryOperation>> curr_syn_ss_ops;
    for (const auto &single_syn_op : single_syn_ops) {
      if (single_syn_op->GetSynonym() == syn) {
        curr_syn_ss_ops.push_back(single_syn_op);
      }
    }
    std::shared_ptr<QNode> rhs_node;
    if (curr_syn_ss_ops.empty()) {
      rhs_node = std::make_shared<EntityNode>(syn);
    } else {
      rhs_node = BuildIntersectTree(curr_syn_ss_ops);
    }

    auto new_head = std::make_shared<JoinNode>();
    new_head->SetLeftNode(head);
    new_head->SetRightNode(rhs_node);
    head = new_head;
  }

  // Add all no syn to wrap over top node
  for (const auto &no_syn_op : no_syn_ops) {
    auto new_head = std::make_shared<BooleanNode>();
    new_head->SetLeftNode(std::make_shared<AbstractionNode>(no_syn_op));
    new_head->SetRightNode(head);
    head = new_head;
  }

  return head;
}

std::shared_ptr<QNode> Planner::BuildQTree(
    std::vector<std::shared_ptr<QueryOperation>> &q_operations) const {
  if (q_operations.empty()) {
    return nullptr;
  }
  // Pop
  std::shared_ptr<QueryOperation> data = q_operations.front();
  q_operations.erase(q_operations.begin());

  std::shared_ptr<QNode> root = std::make_shared<AbstractionNode>(data);
  root->SetLeftNode(BuildQTree(q_operations));
  root->SetRightNode(BuildQTree(q_operations));
  return root;
}

std::shared_ptr<QNode> Planner::BuildIntersectTree(
    const std::vector<std::shared_ptr<QueryOperation>> &operations) const {
  assert(!operations.empty());
  std::shared_ptr<QNode> head;
  for (auto const &op : operations) {
    auto op_node = std::make_shared<AbstractionNode>(op);
    if (head == nullptr) {
      head = op_node;
    } else {
      auto new_head = std::make_shared<IntersectNode>();
      new_head->SetLeftNode(head);
      new_head->SetRightNode(op_node);
      head = new_head;
    }
  }
  return head;
}
