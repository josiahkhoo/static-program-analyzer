#ifndef SPA_REFERENCE_H
#define SPA_REFERENCE_H

#include <optional>
#include <string>

#include "common/entity/entity_type.h"
#include "synonym.h"

class Reference {
 public:
  explicit Reference(bool is_wild_card);

  explicit Reference(Synonym synonym_);

  [[nodiscard]] Synonym GetSynonym() const;

  [[nodiscard]] bool IsSynonym() const;

  [[nodiscard]] bool IsWildCard() const;

  [[nodiscard]] bool IsEntityType(EntityType type) const;

  [[nodiscard]] virtual bool IsLineNumber() const = 0;

  [[nodiscard]] virtual int GetLineNumber() const = 0;

  [[nodiscard]] virtual bool IsIdentifier() const = 0;

  [[nodiscard]] virtual std::string GetIdentifier() const = 0;

  bool operator==(const Reference &rhs) const;

  bool operator!=(const Reference &rhs) const;

 private:
  std::optional<Synonym> synonym_;
  bool is_wild_card_;
};

#endif  // SPA_REFERENCE_H
