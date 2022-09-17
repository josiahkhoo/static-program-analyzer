#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_BOOLEAN_NODE_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_BOOLEAN_NODE_H_

#include "q_node.h"

/// A BooleanNode returns the RHS results if the LHS is a non empty set.
class BooleanNode : public QNode {
 public:
  QResult Fetch(const QueryablePkb& pkb) override;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_BOOLEAN_NODE_H_
