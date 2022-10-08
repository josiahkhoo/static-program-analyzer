#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/entity/entity_type.h"
#include "common/reference/attribute_name.h"
#include "identifier.h"
#include "string"

class Synonym {
 public:
  Synonym(EntityType entity_type, Identifier identifier);

  [[nodiscard]] EntityType GetEntityType();

  [[nodiscard]] Identifier GetIdentifier() const;

  [[nodiscard]] bool IsEntityType(EntityType type) const;

  [[nodiscard]] bool IsValueNotEqualToAttribute(
      AttributeName attribute_name) const;

  bool operator==(const Synonym &rhs) const;

  bool operator!=(const Synonym &rhs) const;

 private:
  EntityType entity_type_;
  Identifier identifier_;
};

#endif  // SPA_SYNONYM_H
