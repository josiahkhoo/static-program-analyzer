#ifndef SPA_QUERY_STRING_BUILDER_H
#define SPA_QUERY_STRING_BUILDER_H

#include "common/clause/follows_clause.h"
#include "common/clause/follows_t_clause.h"
#include "common/clause/select.h"
#include "common/entity/entity.h"
#include "query_string.h"

class QueryStringBuilder {
 public:
  void AddDeclaration(Entity declared_entity);
  void AddSelect(Select select_clause);
  void AddFollows(FollowsClause follows_clause);
  void AddFollowsT(FollowsTClause follows_t_clause);

  QueryString GetQueryString();

 private:
  std::vector<Entity> entities_;
  std::vector<FollowsClause> follows_;
  std::vector<FollowsTClause> follows_ts_;
  Select select_;
};

#endif  // SPA_QUERY_STRING_BUILDER_H
