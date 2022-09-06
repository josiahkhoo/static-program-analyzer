#include "relationship_manager.h"

RelationshipManager::RelationshipManager(){};

void RelationshipManager::AddAbstraction(FollowsAbstraction abstraction) {
  followsStore.AddFollowsRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(FollowsTAbstraction abstraction){
    followsStore.AddFollowsRelationship()};
