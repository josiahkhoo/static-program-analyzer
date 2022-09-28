#include "boolean_node.h"

BooleanNode::BooleanNode(std::shared_ptr<QueryOperation> no_syn_operation)
    : no_syn_operation_(no_syn_operation) {}

QResult BooleanNode::Fetch(const QueryablePkb& pkb) {
  if (!no_syn_operation_->IsTrue(pkb)) {
    return QResult(true);
  }
  return GetRightNode()->Fetch(pkb);
}
