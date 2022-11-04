#include "intersect_node.h"

#include <cassert>

QResult IntersectNode::Fetch(QueryablePkb& pkb) {
  assert(GetLeftNode() != nullptr && GetRightNode() != nullptr);
  return GetLeftNode()->Fetch(pkb).Intersect(GetRightNode()->Fetch(pkb));
}
