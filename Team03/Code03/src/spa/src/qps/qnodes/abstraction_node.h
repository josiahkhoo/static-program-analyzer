#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "q_node.h"
#include "qps/query_tail.h"

class AbstractionNode : public QNode {
 private:
  QueryTail* q_tail_;
 public:
  explicit AbstractionNode(QueryTail* q_tail, QNode* left_node, QNode* right_node);
  std::vector<Entity> Execute(QueryablePkb &pkb) override;
};

#endif  // SPA_ABSTRACTION_NODE_H
