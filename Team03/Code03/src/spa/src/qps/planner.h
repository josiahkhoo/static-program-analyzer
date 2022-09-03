#ifndef SPA_PLANNER_H
#define SPA_PLANNER_H

#include "qps/qnodes/q_node.h"
#include "query_string.h"

class Planner {
 public:
  explicit Planner();
  [[nodiscard]] QNode Plan(const QueryString& q_string) const;
};

#endif  // SPA_PLANNER_H
