#ifndef SPA_PLANNER_H
#define SPA_PLANNER_H

#include "qps/qnodes/q_node.h"
#include "query_string.h"

class Planner {
 public:
  explicit Planner();

  [[nodiscard]] std::shared_ptr<QNode> Plan(const QueryString &q_string) const;

 private:
  [[nodiscard]] std::shared_ptr<QNode> BuildIntersectTree(
      const std::vector<std::shared_ptr<QueryOperation>> &operations) const;
};

#endif  // SPA_PLANNER_H
