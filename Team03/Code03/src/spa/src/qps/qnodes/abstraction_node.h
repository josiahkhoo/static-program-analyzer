#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "common/query_operation.h"
#include "q_node.h"

/// An abstraction node has two purposes:
/// <br/>1. If there is no children, it calls the Fetch operation on the
/// assigned QueryOperation.
/// <br/>2. If there is children, performs a loop based
/// join on the assigned QueryOperation based on the results of the child nodes.
class AbstractionNode : public QNode {
 public:
  explicit AbstractionNode(std::shared_ptr<QueryOperation> q_operation);

  QResult Fetch(QueryablePkb &pkb) override;

 private:
  std::shared_ptr<QueryOperation> q_operation_;

  QResult FetchWithChildren(QueryablePkb &pkb);
};

#endif  // SPA_ABSTRACTION_NODE_H
