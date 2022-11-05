#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_BOOLEAN_NODE_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_BOOLEAN_NODE_H_

#include "common/query_operation.h"
#include "q_node.h"

/// A BooleanNode returns the RHS results if the LHS is a non empty set.
class BooleanNode : public QNode {
 public:
  explicit BooleanNode(std::shared_ptr<QueryOperation> no_syn_operation);
  QResult Fetch(QueryablePkb& pkb) override;

 private:
  std::shared_ptr<QueryOperation> no_syn_operation_;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_BOOLEAN_NODE_H_
