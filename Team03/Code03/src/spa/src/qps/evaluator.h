#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <map>

#include "qps/qnodes/q_node.h"
#include "query_string.h"

class Evaluator {
 public:
  explicit Evaluator();

  [[nodiscard]] std::unordered_set<std::string> Execute(
      const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree,
      const Select& slt) const;
};

#endif  // SPA_EVALUATOR_H
