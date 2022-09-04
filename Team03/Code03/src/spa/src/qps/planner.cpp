#include "planner.h"

#include "qps/qnodes/abstraction_node.h"
#include "qps/qnodes/entity_node.h"
#include "query_string.h"

Planner::Planner() = default;

QNode* Planner::Plan(const QueryString& q_string) {
  Select select_clause = q_string.GetSelect();
  std::vector<Clause> clauses = q_string.GetClause();

  QNode* root;
  if (clauses.empty()) {
    root = new EntityNode(select_clause);
  } else {
    root = BuildQTree(clauses);
  }
  return root;
}

QNode* Planner::BuildQTree(std::vector<Clause>& clauses) const {
  QNode* root;

  if (clauses.empty()) {
    return nullptr;
  }
  Clause data = clauses.front();
  clauses.erase(clauses.begin());

  root = new AbstractionNode(data);
  root->SetLeftNode(BuildQTree(clauses));
  root->SetRightNode(BuildQTree(clauses));
  return root;
}
