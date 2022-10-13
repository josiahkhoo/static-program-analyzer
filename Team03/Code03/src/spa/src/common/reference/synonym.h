#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/entity/entity_type.h"
#include "common/reference/attribute_name.h"
#include "identifier.h"
#include "string"

class Synonym {
 public:
  Synonym(EntityType entity_type, Identifier identifier);

  [[nodiscard]] EntityType GetEntityType() const;

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

namespace std {
template <>
class hash<Synonym> {
 public:
  /// Hash function for Synonym using prime number 196613
  /// \param syn
  /// \return size_t.
  size_t operator()(const Synonym &syn) const {
    return (std::hash<std::string>{}(syn.GetIdentifier())) +
           (syn.GetEntityType() % 196613);
  }
};
}  // namespace std

#endif  // SPA_SYNONYM_H
