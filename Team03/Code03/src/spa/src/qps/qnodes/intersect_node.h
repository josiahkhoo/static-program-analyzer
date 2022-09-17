#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_INTERSECT_NODE_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_INTERSECT_NODE_H_

#include "q_node.h"

/// An intersect node is responsible for finding the intersect between a LHS and
/// RHS query result. See test cases for `QResult` to understand more.
class IntersectNode : public QNode {
 public:
  QResult Fetch(const QueryablePkb& pkb) override;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_INTERSECT_NODE_H_
