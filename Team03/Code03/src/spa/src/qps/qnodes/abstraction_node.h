#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "q_node.h"

class AbstractionNode : public QNode {
 private:
  Clause clause_;

 public:
  explicit AbstractionNode(Clause clause);
  std::vector<std::string> Fetch(QueryablePkb& pkb) override;
};

#endif  // SPA_ABSTRACTION_NODE_H
