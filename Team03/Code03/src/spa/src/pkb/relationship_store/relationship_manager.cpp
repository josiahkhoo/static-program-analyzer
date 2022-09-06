#include "relationship_manager.h"

RelationshipManager::RelationshipManager() {};

void RelationshipManager::AddFollowsAbstraction(FollowsAbstraction followsAbs) {
	followsStore.AddFollowsRelationship(followsAbs);
}

void RelationshipManager::AddFollowsTAbstraction(FollowsTAbstraction followsTAbs) {
	// to implement
}

