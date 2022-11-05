#ifndef SPA_ENTITY_NODE_H
#define SPA_ENTITY_NODE_H

#include "common/clause/select.h"
#include "q_node.h"
#include "q_result.h"

/// An entity node is responsible for directly calling the PKB for all possible
/// values of a specific synonym individually.
class EntityNode : public QNode {
 private:
  Synonym synonym_;

 public:
  explicit EntityNode(Synonym synonym);

  QResult Fetch(QueryablePkb &pkb) override;
};

#endif  // SPA_ENTITY_NODE_H
