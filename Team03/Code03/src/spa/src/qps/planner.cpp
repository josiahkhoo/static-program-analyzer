#include "planner.h"

#include "qps/qnodes/abstraction_node.h"
#include "qps/qnodes/entity_node.h"
#include "query_string.h"

Planner::Planner() = default;

std::shared_ptr<QNode> Planner::Plan(const QueryString &q_string) const {
  Select select_clause = q_string.GetSelect();
  std::vector<std::shared_ptr<QueryOperation>> q_operations =
      q_string.GetQueryOperation();

  if (q_operations.empty()) {
    return std::make_shared<EntityNode>(select_clause);
  }
  return BuildQTree(q_operations);
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
