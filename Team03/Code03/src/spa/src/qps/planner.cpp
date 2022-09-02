#include "planner.h"

QNode Planner::Plan(const QueryString& q_string) const {
  SelectClause select_clause = q_string.GetSelectClause();
  std::vector<QueryTail> tails = q_string.GetTails();

  return QNode(nullptr, nullptr);
}
