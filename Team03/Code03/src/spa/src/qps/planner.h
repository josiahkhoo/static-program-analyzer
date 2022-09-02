#ifndef SPA_PLANNER_H
#define SPA_PLANNER_H

#include "qps/qnodes/entity_node.h"
#include "query_string.h"

class Planner {
 public:
  [[nodiscard]] EntityNode Plan(const QueryString& q_string) const;
};

#endif  // SPA_PLANNER_H
