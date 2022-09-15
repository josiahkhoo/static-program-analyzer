#ifndef SPA_Q_NODE_H
#define SPA_Q_NODE_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/entity/entity.h"
#include "common/queryable_pkb.h"

class QNode {
 public:
  explicit QNode(std::string syn);

  void SetLeftNode(std::shared_ptr<QNode> left_node);

  void SetRightNode(std::shared_ptr<QNode> right_node);

  [[nodiscard]] std::shared_ptr<QNode> GetLeftNode() const;

  [[nodiscard]] std::shared_ptr<QNode> GetRightNode() const;

  [[nodiscard]] bool IsLeaf() const;

  virtual std::unordered_set<std::string> Fetch(const QueryablePkb &pkb);

 private:
  std::string syn_;
  std::shared_ptr<QNode> left_node_;
  std::shared_ptr<QNode> right_node_;
};

#endif  // SPA_Q_NODE_H
