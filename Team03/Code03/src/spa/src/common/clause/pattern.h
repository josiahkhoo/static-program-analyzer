#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "common/pair.h"
#include "common/reference/entity_reference.h"

class Pattern : public Pair<EntityReference, std::string> {
 public:
  explicit Pattern(EntityReference entity, std::string expression);

  [[nodiscard]] const EntityReference &GetEntity() const;

  [[nodiscard]] const std::string &GetExpression() const;

 private:
  EntityReference entity_;
  std::string expression_;
};

#endif  // SPA_PATTERN_H
