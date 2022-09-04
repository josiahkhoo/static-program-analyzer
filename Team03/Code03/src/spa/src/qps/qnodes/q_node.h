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
  explicit QNode();
  void SetLeftNode(QNode* leftNode);
  void SetRightNode(QNode* rightNode);
  [[nodiscard]] QNode* GetLeftNode() const;
  [[nodiscard]] QNode* GetRightNode() const;
  [[nodiscard]] bool IsLeaf() const;
  virtual std::vector<std::string> Fetch(QueryablePkb &pkb);
};

#endif  // SPA_Q_NODE_H
