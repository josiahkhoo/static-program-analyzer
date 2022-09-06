#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "common/pair.h"
#include "common/reference/entity_reference.h"

struct Expression {
  bool hasFrontWildcard = false;
  std::string toMatch = "";
  bool hasBackWildcard = false;
};

class Pattern {
 public:
  explicit Pattern(EntityReference entity, Expression expression);

  [[nodiscard]] const EntityReference &GetEntity() const;
  [[nodiscard]] const Expression &GetExpression() const;

 private:
  EntityReference entity_;
  Expression expression_;
};

#endif  // SPA_PATTERN_H
