#ifndef SPA_ENTITY_REFERENCE_H
#define SPA_ENTITY_REFERENCE_H

#include <optional>

#include "reference.h"

class EntityReference : public Reference {
 public:
  explicit EntityReference();
  [[nodiscard]] std::optional<std::string> GetIdentifier() const;
  [[nodiscard]] bool IsIdentifier() const;

  void SetIdentifier(const std::string& identifier);

 private:
  std::optional<std::string> identifier_;
};

#endif  // SPA_ENTITY_REFERENCE_H
