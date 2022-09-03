#include "planner.h"

#include "qps/qnodes/abstraction_node.h"
#include "qps/qnodes/entity_node.h"
#include "query_string.h"

Planner::Planner() = default;

QNode Planner::Plan(const QueryString& q_string) const {
  Select select_clause = q_string.GetSelect();
  std::vector<SuchThat> clauses = q_string.GetSuchThat();

  if (clauses.empty()) {
    return EntityNode(&select_clause, nullptr, nullptr);
  }

  // Back to Front clause sequence
  std::shared_ptr<QNode> curr = nullptr;
  for(int i = clauses.size() - 1; i >= 0; i--) {
    SuchThat base = clauses[i];
    AbstractionNode aNode = AbstractionNode(&base, curr, nullptr);
    curr = std::shared_ptr<QNode>(&aNode);
  }
  return *curr;
}

