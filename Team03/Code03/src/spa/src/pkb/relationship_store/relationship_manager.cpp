#include "relationship_manager.h"

void RelationshipManager::AddAbstraction(FollowsAbstraction abstraction) {
  follows_store.AddRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(FollowsTAbstraction abstraction) {
  follows_store.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(ParentAbstraction abstraction) {
  parent_store.AddRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(ParentTAbstraction abstraction) {
  parent_store.AddRelationship(abstraction);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsStatements()
    const {
  return follows_store.GetFollowsStatements();
}

std::unordered_set<std::string> RelationshipManager::GetFollowsStatements(
    int statement_number) const {
  return follows_store.GetFollowsStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsTStatements(
    int statement_number) const {
  return follows_store.GetFollowsTStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements(
    int statement_number) const {
  return follows_store.GetFollowsByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements()
    const {
  return follows_store.GetFollowsByStatements();
}

std::unordered_set<std::string> RelationshipManager::GetFollowsTByStatements(
    int statement_number) const {
  return follows_store.GetFollowsTByStatements(statement_number);
}
