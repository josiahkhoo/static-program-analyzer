#include "planner.h"

#include <cassert>
#include <unordered_map>

#include "qps/qnodes/abstraction_node.h"
#include "qps/qnodes/boolean_node.h"
#include "qps/qnodes/entity_node.h"
#include "qps/qnodes/intersect_node.h"
#include "qps/qnodes/join_node.h"
#include "query_string.h"

Planner::Planner() = default;

std::shared_ptr<QNode> Planner::Plan(const QueryString &q_string) const {
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
  CreateAbstractionNodes(single_syn_ops, double_syn_ops, abstraction_nodes,
                         abstraction_node_to_query_op_map);

  // Assemble abstraction nodes
  std::unordered_set<std::shared_ptr<QNode>> disjoint_join_nodes;
  CreateDisjointJoinNodes(abstraction_nodes, abstraction_node_to_query_op_map,
                          disjoint_join_nodes);

  // Combine disjoint join nodes via join operation
  std::shared_ptr<QNode> head = std::make_shared<QNode>();
  head = ConnectDisjointNodes(disjoint_join_nodes, head);

  // Add all unused synonyms that are part of the select node to RHS of the top
  // node
  head = ConnectUnusedSynonyms(q_string, single_syn_ops, double_syn_ops, head);

  // Add all no syn to wrap over top node
  head = ConnectBooleanNodes(no_syn_ops, head);

  return head;
}

void Planner::CreateAbstractionNodes(
    const std::vector<std::shared_ptr<QueryOperation>> &single_syn_ops,
    const std::vector<std::shared_ptr<QueryOperation>> &double_syn_ops,
    std::vector<std::shared_ptr<QNode>> &abstraction_nodes,
    std::unordered_map<std::shared_ptr<QNode>, std::shared_ptr<QueryOperation>>
        &abstraction_node_to_query_op_map) const {
  std::unordered_set<std::shared_ptr<QueryOperation>> seen_single_ops;
  for (const auto &double_syn_op : double_syn_ops) {
    // Find all relevant single syn ops
    std::vector<std::shared_ptr<QueryOperation>> lhs_single_syn_ops,
        rhs_single_syn_ops;
    auto [lhs_syn, rhs_syn] = double_syn_op->GetSynonymPair();
    for (const auto &single_syn_op : single_syn_ops) {
      if (single_syn_op->GetSynonym() == lhs_syn) {
        // Find if LHS has single syn op
        lhs_single_syn_ops.push_back(single_syn_op);
        seen_single_ops.insert(single_syn_op);
      } else if (single_syn_op->GetSynonym() == rhs_syn) {
        // Find if RHS has single syn op
        rhs_single_syn_ops.push_back(single_syn_op);
        seen_single_ops.insert(single_syn_op);
      }
    }

    // Add single syn ops if either one is empty
    std::shared_ptr<QNode> lhs_node, rhs_node;
    if (lhs_single_syn_ops.empty()) {
      lhs_node = std::make_shared<EntityNode>(lhs_syn);
    } else {
      lhs_node = this->BuildIntersectTree(lhs_single_syn_ops);
    }
    if (rhs_single_syn_ops.empty()) {
      rhs_node = std::make_shared<EntityNode>(rhs_syn);
    } else {
      rhs_node = this->BuildIntersectTree(rhs_single_syn_ops);
    }

    // Create an abstraction node WITH children
    auto abstraction_node = std::make_shared<AbstractionNode>(double_syn_op);
    abstraction_node->SetLeftNode(lhs_node);
    abstraction_node->SetRightNode(rhs_node);

    // Add to list of abstraction nodes
    abstraction_nodes.push_back(abstraction_node);
    // Add to abstraction node -> query operator map
    abstraction_node_to_query_op_map.insert(
        std::make_pair(abstraction_node, double_syn_op));
  }

  for (const auto &single_syn_op : single_syn_ops) {
    if (seen_single_ops.find(single_syn_op) == seen_single_ops.end()) {
      // Create single syn op abstraction node
      auto abstraction_node = std::make_shared<AbstractionNode>(single_syn_op);
      // Add to list of abstraction nodes
      abstraction_nodes.push_back(abstraction_node);
      // Add to abstraction node -> query operator map
      abstraction_node_to_query_op_map.insert(
          std::make_pair(abstraction_node, single_syn_op));
    }
  }
}

void Planner::CreateDisjointJoinNodes(
    const std::vector<std::shared_ptr<QNode>> &abstraction_nodes,
    std::unordered_map<std::shared_ptr<QNode>, std::shared_ptr<QueryOperation>>
        &abstraction_node_to_query_op_map,
    std::unordered_set<std::shared_ptr<QNode>> &disjoint_join_nodes) const {
  std::unordered_set<std::shared_ptr<QNode>> seen;
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
          // If not seen compare node1_op if it's common with node2_op
          if (node1_op->IsRelatedTo(node2_op.get())) {
            // Make current node left hand child of new node
            // and make node 2 right hand child of new node,
            // then swap new node and current node
            auto new_node = std::make_shared<JoinNode>();
            new_node->SetLeftNode(current_node);
            new_node->SetRightNode(node2);
            current_node = new_node;
          }
        }
      }
      // Add current node to disjoint join nodes after iteration
      disjoint_join_nodes.emplace(current_node);
    }
  }
}

std::shared_ptr<QNode> Planner::ConnectDisjointNodes(
    std::unordered_set<std::shared_ptr<QNode>> &disjoint_join_nodes,
    std::shared_ptr<QNode> &head) const {
  auto curr_head = head;
  for (const auto &node : disjoint_join_nodes) {
    auto new_head = std::make_shared<JoinNode>();
    new_head->SetLeftNode(curr_head);
    new_head->SetRightNode(node);
    curr_head = new_head;
  }
  return curr_head;
}

std::shared_ptr<QNode> Planner::ConnectUnusedSynonyms(
    const QueryString &q_string,
    const std::vector<std::shared_ptr<QueryOperation>> &single_syn_ops,
    const std::vector<std::shared_ptr<QueryOperation>> &double_syn_ops,
    std::shared_ptr<QNode> &head) const {
  auto curr_head = head;
  for (const auto &syn : q_string.GetSynonyms()) {
    // Check if used
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

    // Check if synonym is part of select node
    bool part_of = false;
    for (const auto &syn_with_attr : q_string.GetSelect()->GetSynonyms()) {
      if (syn == syn_with_attr.synonym) {
        part_of = true;
        break;
      }
    }
    if (!part_of) {
      // Skip if synonym is not part of select node
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
      rhs_node = this->BuildIntersectTree(curr_syn_ss_ops);
    }

    auto new_head = std::make_shared<JoinNode>();
    new_head->SetLeftNode(curr_head);
    new_head->SetRightNode(rhs_node);
    curr_head = new_head;
  }
  return curr_head;
}

std::shared_ptr<QNode> Planner::ConnectBooleanNodes(
    const std::vector<std::shared_ptr<QueryOperation>> &no_syn_ops,
    std::shared_ptr<QNode> &head) const {
  std::shared_ptr<QNode> curr_head = head;
  for (const auto &no_syn_op : no_syn_ops) {
    auto new_head = std::make_shared<BooleanNode>(no_syn_op);
    new_head->SetRightNode(curr_head);
    curr_head = new_head;
  }
  return curr_head;
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
