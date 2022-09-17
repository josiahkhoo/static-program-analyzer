#ifndef SPA_ENTITY_NODE_H
#define SPA_ENTITY_NODE_H

#include "common/clause/select.h"
#include "q_node.h"
#include "q_result.h"

class EntityNode : public QNode {
 private:
  Synonym synonym_;

 public:
  explicit EntityNode(Synonym synonym);

  QResult Fetch(const QueryablePkb &pkb) override;
};

#endif  // SPA_ENTITY_NODE_H
