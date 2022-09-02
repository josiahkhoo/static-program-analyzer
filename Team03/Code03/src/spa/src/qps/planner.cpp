#include "planner.h"

#include "qps/qnodes/entity_node.h"
#include "query_string.h"

EntityNode Planner::Plan(const QueryString& q_string) const {
  Select select_clause = q_string.GetSelect();
  std::vector<FollowsClause> f_clauses = q_string.GetFollows();

  return EntityNode(&select_clause, nullptr, nullptr);
}
