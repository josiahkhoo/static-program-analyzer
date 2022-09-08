#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "common/pair.h"
#include "common/query_operation.h"
#include "common/reference/entity_reference.h"

struct Expression {
  bool hasFrontWildcard = false;
  std::string toMatch = "";
  bool hasBackWildcard = false;
};

class Pattern : public QueryOperation {
 public:
  explicit Pattern(EntityReference entity, Expression expression);

  [[nodiscard]] const EntityReference &GetEntity() const;
  [[nodiscard]] const Expression &GetExpression() const;
  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

 private:
  EntityReference entity_;
  Expression expression_;
};

#endif  // SPA_PATTERN_H
