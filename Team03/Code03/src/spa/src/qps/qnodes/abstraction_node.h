#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "common/query_operation.h"
#include "q_node.h"

class AbstractionNode : public QNode {
 public:
  explicit AbstractionNode(std::shared_ptr<QueryOperation> q_operation);

  std::unordered_set<std::string> Fetch(const QueryablePkb &pkb) override;

 private:
  std::shared_ptr<QueryOperation> q_operation_;
};

#endif  // SPA_ABSTRACTION_NODE_H
