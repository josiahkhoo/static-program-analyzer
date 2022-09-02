#include "entity_node.h"

EntityNode::EntityNode(SelectClause* select, QNode* left_node,
                                 QNode* right_node) : QNode(left_node, right_node) {
  select_ = select;
}

std::vector<Entity> EntityNode::Execute(QueryablePkb& pkb) {
  if (this->IsLeaf()) {
    return select_->Filter(pkb);
  } else {
  }
}
