#ifndef SPA_Q_NODE_H
#define SPA_Q_NODE_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/entity/entity.h"
#include "common/queryable_pkb.h"
#include "q_result.h"

/// Base QNode that by default returns an empty QResult.
class QNode {
 public:
  explicit QNode();

  virtual ~QNode() = default;

  void SetLeftNode(std::shared_ptr<QNode> left_node);

  void SetRightNode(std::shared_ptr<QNode> right_node);

  [[nodiscard]] std::shared_ptr<QNode> GetLeftNode() const;

  [[nodiscard]] std::shared_ptr<QNode> GetRightNode() const;

  virtual QResult Fetch(QueryablePkb &pkb);

 private:
  std::shared_ptr<QNode> left_node_;
  std::shared_ptr<QNode> right_node_;
};

#endif  // SPA_Q_NODE_H
