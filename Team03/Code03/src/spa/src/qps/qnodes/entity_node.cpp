#include "entity_node.h"

#include <utility>

EntityNode::EntityNode(Select select)
    : QNode(select.GetSynonym().GetIdentifier()), select_(std::move(select)) {}

std::map<std::string, std::unordered_set<std::string>> EntityNode::Fetch(
    const QueryablePkb &pkb) {
  std::map<std::string, std::unordered_set<std::string>> map_of_results;
  map_of_results.insert({select_.GetSynonym().GetIdentifier(),
                         pkb.QueryAll(select_.GetSynonym().GetEntityType())});
  return map_of_results;
}
