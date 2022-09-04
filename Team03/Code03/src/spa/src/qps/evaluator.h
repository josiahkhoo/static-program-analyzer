#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include "qps/qnodes/q_node.h"
#include "query_string.h"

class Evaluator {
 public:
  explicit Evaluator();
  [[nodiscard]] std::vector<std::string> Execute(QueryablePkb& pkb,
                                                 QNode* q_tree) const;
};

#endif  // SPA_EVALUATOR_H
