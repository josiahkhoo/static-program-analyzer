//
// Created by Josiah Khoo on 17/9/22.
//

#include "intersect_node.h"

QResult IntersectNode::Fetch(const QueryablePkb& pkb) {
  assert(GetLeftNode() != nullptr && GetRightNode() != nullptr);
  return GetLeftNode()->Fetch(pkb).Intersect(GetRightNode()->Fetch(pkb));
}
