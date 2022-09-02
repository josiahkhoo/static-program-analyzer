#ifndef SPA_FOLLOWS_NODE_H
#define SPA_FOLLOWS_NODE_H

#include "q_node.h"

class FollowsNode : public QNode {
 private:
  FollowsClause clause_;
 public:
  explicit FollowsNode(FollowsClause* clause, QNode* left_node,
                           QNode* right_node);
  std::vector<Entity> Execute(QueryablePkb &pkb) override;
};

#endif  // SPA_FOLLOWS_NODE_H
