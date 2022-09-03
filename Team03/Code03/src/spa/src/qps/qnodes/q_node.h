#ifndef SPA_Q_NODE_H
#define SPA_Q_NODE_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/entity/entity.h"
#include "common/queryable_pkb.h"

class QNode {
 private:
  std::shared_ptr<QNode> left_node_;
  std::shared_ptr<QNode> right_node_;

 public:
  explicit QNode(std::shared_ptr<QNode> left_node,
                 std::shared_ptr<QNode> right_node);
  std::vector<Entity> Execute(QueryablePkb &pkb);
  [[nodiscard]] bool IsLeaf() const;
};

#endif  // SPA_Q_NODE_H
