#ifndef SPA_ENTITY_REFERENCE_H
#define SPA_ENTITY_REFERENCE_H

#include <string>

#include "optional"
#include "reference.h"

class EntityReference : public Reference {
 public:
  std::optional<std::string> GetIdentifier() const;
  std::optional<std::string> GetSynonym() const;
  bool IsIdentifier() const;
  bool IsSynonym() const;
  bool IsWildCard() const;
};

#endif  // SPA_ENTITY_REFERENCE_H
