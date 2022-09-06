#include "follows_storage.h"
#include "follows_relationship.h"

static std::unordered_map<int, FollowsRelationship*> FollowsStorage::followsMap;

FollowsStorage::FollowsStorage() {}

void FollowsStorage::AddFollowsRelationship(FollowsAbstraction followsAbs) {
  int following_statement = followsAbs.GetRightHandSide().GetStatementNumber;
  int followed_statement = followsAbs.GetLeftHandSide().GetStatementNumber;

  // initialise empty fields with -1
  FollowsRelationship * following = new FollowsRelationship(followed_statement, -1);
  FollowsRelationship * followed = new FollowsRelationship(-1, following_statement);
  followsMap[following_statement] = following;
  followsMap[followed_statement] = followed;
}

std::unordered_map<int, FollowsRelationship*> FollowsStorage::GetFollows(); {
  return followsMap;
}

void FollowsStorage::Clear() { 
  for (auto const& pair : m) {
    FollowsRelationship* relationship = pair.second;
    delete relationship;
  }
  followsMap.clear(); 
}
