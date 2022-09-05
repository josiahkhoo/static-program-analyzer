#ifndef SPA_ENTITY_REFERENCE_H
#define SPA_ENTITY_REFERENCE_H

#include <optional>

#include "reference.h"

class EntityReference : public Reference {
 public:
  /// Default constructor creates a wildcard entity reference.
  explicit EntityReference();
  explicit EntityReference(std::string identifier);
  explicit EntityReference(Synonym synonym);
  [[nodiscard]] bool IsIdentifier() const;
  [[nodiscard]] std::string GetIdentifier() const;

 private:
  std::optional<std::string> identifier_;
};

#endif  // SPA_ENTITY_REFERENCE_H
