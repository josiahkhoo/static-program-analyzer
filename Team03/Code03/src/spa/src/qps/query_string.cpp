#include "query_string.h"

#include <utility>

QueryString::QueryString(Select select, std::vector<Entity> entities,
                         std::vector<FollowsClause> follows,
                         std::vector<FollowsTClause> followsTs)
    : select_(std::move(select)), entities_(std::move(entities)),
      follows_(std::move(follows)), follows_ts_(std::move(followsTs)) {}

Select QueryString::GetSelect() const {
  return select_;
}

const std::vector<Entity>& QueryString::GetEntities() const {
  return entities_;
}

const std::vector<FollowsClause>& QueryString::GetFollows() const {
  return follows_;
}

const std::vector<FollowsTClause>& QueryString::GetFollowsTs() const {
  return follows_ts_;
}
