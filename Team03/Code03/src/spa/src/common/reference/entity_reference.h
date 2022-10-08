#ifndef SPA_ENTITY_REFERENCE_H
#define SPA_ENTITY_REFERENCE_H

#include <optional>

#include "identifier.h"
#include "integer.h"
#include "reference.h"

class EntityReference : public Reference {
 public:
  /// Default constructor creates a wildcard entity reference.
  explicit EntityReference();

  explicit EntityReference(Identifier identifier);

  explicit EntityReference(Synonym synonym);

  [[nodiscard]] bool IsLineNumber() const override;

  [[nodiscard]] Integer GetLineNumber() const override;

  [[nodiscard]] bool IsIdentifier() const override;

  [[nodiscard]] Identifier GetIdentifier() const override;

 private:
  std::optional<Identifier> identifier_;
};

#endif  // SPA_ENTITY_REFERENCE_H
