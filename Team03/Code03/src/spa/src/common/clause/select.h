#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include "common/reference/entity_reference.h"

class Select {
 public:
  explicit Select(EntityReference entity);
  [[nodiscard]] const EntityReference &GetEntity() const;

 private:
  EntityReference entity_;
};

#endif  // SPA_SELECT_H
