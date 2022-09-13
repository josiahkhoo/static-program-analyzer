#include "relationship_manager.h"

void RelationshipManager::AddAbstraction(FollowsAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(FollowsTAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(ParentAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(ParentTAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsStatements()
    const {
  return follows_store_.GetFollowsStatements();
}

std::unordered_set<std::string> RelationshipManager::GetFollowsStatements(
    int statement_number) const {
  return follows_store_.GetFollowsStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsTStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements()
    const {
  return follows_store_.GetFollowsByStatements();
}

std::unordered_set<std::string> RelationshipManager::GetFollowsTByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentStatements()
    const {
  return parent_store_.GetParentStatements();
}

std::unordered_set<std::string> RelationshipManager::GetParentStatements(
    int statement_number) const {
  return parent_store_.GetParentStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentTStatements(
    int statement_number) const {
  return parent_store_.GetParentTStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentByStatements(
    int statement_number) const {
  return parent_store_.GetParentByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentByStatements()
    const {
  return parent_store_.GetParentByStatements();
}

std::unordered_set<std::string> RelationshipManager::GetParentTByStatements(
    int statement_number) const {
  return parent_store_.GetParentTByStatements(statement_number);
}

void RelationshipManager::Clear() {
  //  follows_store_.Clear();
  parent_store_.Clear();
}
