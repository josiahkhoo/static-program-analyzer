#ifndef SPA_STATEMENT_REFERENCE_H
#define SPA_STATEMENT_REFERENCE_H

#include <optional>
#include <string>

#include "reference.h"

class StatementReference : public Reference {
 public:
  std::optional<int> GetLineNumber() const;
  std::optional<std::string> GetSynonym() const;
  bool IsLineNumber() const;
  bool IsSynonym() const;
  bool IsWildCard() const;
};

#endif  // SPA_STATEMENT_REFERENCE_H
