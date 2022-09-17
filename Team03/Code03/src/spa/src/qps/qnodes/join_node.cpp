#include "join_node.h"

QResult JoinNode::Fetch(const QueryablePkb& pkb) {
  assert(GetLeftNode() != nullptr && GetRightNode() != nullptr);
  return GetLeftNode()->Fetch(pkb).Join(GetRightNode()->Fetch(pkb));
}
