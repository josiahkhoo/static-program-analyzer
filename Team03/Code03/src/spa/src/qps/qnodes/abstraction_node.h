#ifndef SPA_ABSTRACTION_NODE_H
#define SPA_ABSTRACTION_NODE_H

#include "common/clause/clause.h"
#include "q_node.h"

class AbstractionNode : public QNode {
 public:
  explicit AbstractionNode(std::shared_ptr<Clause> clause);

  std::unordered_set<std::string> Fetch(const QueryablePkb &pkb) override;

 private:
  std::shared_ptr<Clause> clause_;
};

#endif  // SPA_ABSTRACTION_NODE_H
