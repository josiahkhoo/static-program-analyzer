#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "common/pair.h"
#include "common/query_operation.h"
#include "common/reference/entity_reference.h"
#include "common/reference/expression.h"

class Pattern : public QueryOperation {
 public:
  explicit Pattern(Synonym syn, EntityReference entity, Expression expression);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const EntityReference &GetEntity() const;

  [[nodiscard]] const Expression &GetExpression() const;

  [[nodiscard]] std::string GetSyn() const override;

 private:
  std::string syn_;
  EntityReference entity_;
  Expression expression_;
};

#endif  // SPA_PATTERN_H
