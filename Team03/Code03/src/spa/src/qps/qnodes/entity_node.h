#ifndef SPA_ENTITY_NODE_H
#define SPA_ENTITY_NODE_H

#include "common/clause/select.h"
#include "q_node.h"

class EntityNode : public QNode {
 private:
  Select select_;

 public:
  explicit EntityNode(Select select);
  std::unordered_set<std::string> Fetch(const QueryablePkb& pkb) override;
};

#endif  // SPA_ENTITY_NODE_H
