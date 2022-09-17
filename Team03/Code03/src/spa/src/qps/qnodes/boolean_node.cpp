#include "boolean_node.h"

QResult BooleanNode::Fetch(const QueryablePkb& pkb) {
  // If left hand side returns something, return right hand side
  assert(GetLeftNode() != nullptr && GetRightNode() != nullptr);
  QResult res = GetRightNode()->Fetch(pkb);
  if (GetLeftNode()->Fetch(pkb).GetRows().empty()) {
    return {{}, res.GetSynonyms()};
  }
  return res;
}
