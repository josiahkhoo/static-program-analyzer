#include "abstraction_node.h"

#include <utility>

#include "common/clause/clause.h"

AbstractionNode::AbstractionNode(std::shared_ptr<Clause> clause)
    : QNode(), clause_(std::move(clause)) {}

std::unordered_set<std::string> AbstractionNode::Fetch(
    const QueryablePkb& pkb) {
  return clause_->Fetch(pkb);
}
