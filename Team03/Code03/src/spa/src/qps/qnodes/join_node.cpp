#include "join_node.h"

#include <cassert>

QResult JoinNode::Fetch(QueryablePkb& pkb) {
  assert(GetLeftNode() != nullptr && GetRightNode() != nullptr);
  return GetLeftNode()->Fetch(pkb).Join(GetRightNode()->Fetch(pkb));
}
