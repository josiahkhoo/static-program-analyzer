#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "q_node.h"

class AbstractionNode : public QNode {
 private:
  SuchThat clause_;

 public:
  explicit AbstractionNode(SuchThat* clause, QNode* left_node,
                           QNode* right_node);
  std::vector<Entity> Execute(QueryablePkb& pkb) override;
};

#endif  // SPA_ABSTRACTION_NODE_H
