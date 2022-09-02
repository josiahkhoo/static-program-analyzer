#include "query_string_builder.h"

void QueryStringBuilder::AddDeclaration(Entity declared_entity) {
  entities_.push_back(declared_entity);
}

void QueryStringBuilder::AddSelect(Select select_clause) {
  select_ = std::move(select_clause);
}

void QueryStringBuilder::AddFollows(FollowsClause follows_clause) {
  follows_.push_back(follows_clause);
}

void QueryStringBuilder::AddFollowsT(FollowsTClause follows_t_clause) {
  follows_ts_.push_back(follows_t_clause);
}

QueryString QueryStringBuilder::GetQueryString() {
  return QueryString(select_, entities_, follows_, follows_ts_);
}
