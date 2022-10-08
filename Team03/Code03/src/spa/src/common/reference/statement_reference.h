#ifndef SPA_STATEMENT_REFERENCE_H
#define SPA_STATEMENT_REFERENCE_H

#include <optional>

#include "reference.h"

class StatementReference : public Reference {
 public:
  /// Default constructor creates a wildcard statement reference.
  explicit StatementReference();

  explicit StatementReference(Integer line_number);

  explicit StatementReference(Synonym synonym);

  [[nodiscard]] bool IsLineNumber() const override;

  [[nodiscard]] Integer GetLineNumber() const override;

  [[nodiscard]] bool IsIdentifier() const override;

  [[nodiscard]] Identifier GetIdentifier() const override;

 private:
  std::optional<Integer> line_number_;
};

#endif  // SPA_STATEMENT_REFERENCE_H
