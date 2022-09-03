#ifndef SPA_ENTITY_NODE_H
#define SPA_ENTITY_NODE_H

#include "common/clause/select.h"
#include "q_node.h"

class EntityNode : public QNode {
 private:
  Select* select_;
 public:
  explicit EntityNode(Select* select, std::shared_ptr<QNode> left_node,
                 std::shared_ptr<QNode> right_node);
  std::vector<Entity> Execute(QueryablePkb &pkb);
};

#endif  // SPA_ENTITY_NODE_H
