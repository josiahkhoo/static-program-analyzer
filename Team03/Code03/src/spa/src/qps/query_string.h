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
  explicit QueryString(Select select, std::vector<EntityReference> entities,
                       std::vector<Clause> clauses);
  [[nodiscard]] Select GetSelect() const;
  [[nodiscard]] const std::vector<EntityReference>& GetEntities() const;
  [[nodiscard]] const std::vector<Clause>& GetClause() const;

 private:
  std::vector<EntityReference> entities_;
  std::vector<Clause> clauses_;
  Select select_;
};

#endif  // SPA_QUERY_STRING_H