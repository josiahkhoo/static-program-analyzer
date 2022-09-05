#include "planner.h"

#include "qps/qnodes/abstraction_node.h"
#include "qps/qnodes/entity_node.h"
#include "query_string.h"

Planner::Planner() = default;

std::shared_ptr<QNode> Planner::Plan(const QueryString& q_string) const {
  Select select_clause = q_string.GetSelect();
  std::vector<std::shared_ptr<Clause>> clauses = q_string.GetClauses();

  if (clauses.empty()) {
    return std::make_shared<EntityNode>(select_clause);
  }
  return BuildQTree(clauses);
}

std::shared_ptr<QNode> Planner::BuildQTree(
    std::vector<std::shared_ptr<Clause>>& clauses) const {
  if (clauses.empty()) {
    return nullptr;
  }
  std::shared_ptr<Clause> data = clauses.front();
  clauses.erase(clauses.begin());

  std::shared_ptr<QNode> root = std::make_shared<AbstractionNode>(data);
  root->SetLeftNode(BuildQTree(clauses));
  root->SetRightNode(BuildQTree(clauses));
  return root;
}
