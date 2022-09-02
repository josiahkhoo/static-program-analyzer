#ifndef SPA_STATEMENT_REFERENCE_H
#define SPA_STATEMENT_REFERENCE_H

#include <optional>

#include "reference.h"

class StatementReference : public Reference {
 public:
  explicit StatementReference();
  [[nodiscard]] std::optional<int> GetLineNumber() const;
  [[nodiscard]] bool IsLineNumber() const;

  void SetLineNumber(const std::string& line_no);

 private:
  std::optional<int> line_no_;
};

#endif  // SPA_STATEMENT_REFERENCE_H
