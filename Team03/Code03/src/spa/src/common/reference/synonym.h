#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/entity/entity_type.h"
#include "string"

class Synonym {
 public:
  Synonym(EntityType entity_type, std::string identifier);
  [[nodiscard]] EntityType GetEntityType();
  [[nodiscard]] std::string GetIdentifier();
  bool operator==(const Synonym& rhs) const;
  bool operator!=(const Synonym& rhs) const;

 private:
  EntityType entity_type_;
  std::string identifier_;
};

#endif  // SPA_SYNONYM_H
