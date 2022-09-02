#ifndef SPA_QUERY_STRING_H
#define SPA_QUERY_STRING_H

#include <vector>

#include "common/clause/clause.h"
#include "common/clause/follows_clause.h"
#include "common/clause/follows_t_clause.h"
#include "common/clause/select.h"
#include "common/entity/entity.h"

class QueryString {
 public:
  explicit QueryString(Select select, std::vector<Entity> entities, std::vector<FollowsClause> follows, std::vector<FollowsTClause> followsTs);

  [[nodiscard]] Select GetSelect() const;
  [[nodiscard]] const std::vector<Entity>& GetEntities() const;
  [[nodiscard]] const std::vector<FollowsClause>& GetFollows() const;
  [[nodiscard]] const std::vector<FollowsTClause>& GetFollowsTs() const;

 private:
  std::vector<Entity> entities_;
  std::vector<FollowsClause> follows_;
  std::vector<FollowsTClause> follows_ts_;
  Select select_;
};

#endif  // SPA_QUERY_STRING_H