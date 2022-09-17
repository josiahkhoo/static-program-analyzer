#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_JOIN_NODE_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_JOIN_NODE_H_

#include "q_node.h"

/// The Join Node is responsible for joining the results of two nodes together
/// via common synonyms. During the join, it also makes sure that entities are
/// not repeated across declarations.
class JoinNode : public QNode {
 public:
  QResult Fetch(const QueryablePkb& pkb) override;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_JOIN_NODE_H_
