#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "q_node.h"

class AbstractionNode : public QNode {
 private:
  SuchThat* clause_;

 public:
  explicit AbstractionNode(SuchThat* clause, std::shared_ptr<QNode> left_node,
                           std::shared_ptr<QNode> right_node);
  std::vector<Entity> Execute(QueryablePkb &pkb);
};

#endif  // SPA_ABSTRACTION_NODE_H
