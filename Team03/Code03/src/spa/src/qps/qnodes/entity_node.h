#ifndef SPA_ENTITY_NODE_H
#define SPA_ENTITY_NODE_H

#include "q_node.h"
#include "qps/query_tail.h"
#include "qps/select_clause.h"

class EntityNode : public QNode {
 private:
  SelectClause* select_;
 public:
  explicit EntityNode(SelectClause* select, QNode* left_node, QNode* right_node);
  std::vector<Entity> Execute(QueryablePkb &pkb) override;
};

#endif  // SPA_ABSTRACTION_NODE_H
