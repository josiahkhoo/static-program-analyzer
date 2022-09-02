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
  QNode* left_node_;
  QNode* right_node_;
 public:
  explicit QNode(QNode* left_node, QNode* right_node);
  virtual std::vector<Entity> Execute(QueryablePkb &pkb) = 0;
  [[nodiscard]] bool IsLeaf() const;
};

#endif  // SPA_Q_NODE_H
