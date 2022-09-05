#ifndef SPA_STATEMENT_REFERENCE_H
#define SPA_STATEMENT_REFERENCE_H

#include <optional>

#include "reference.h"

class StatementReference : public Reference {
public:
    /// Default constructor creates a wildcard statement reference.
    explicit StatementReference();

    explicit StatementReference(int line_number);

    explicit StatementReference(Synonym synonym);

    [[nodiscard]] bool IsLineNumber() const override;

    [[nodiscard]] int GetLineNumber() const override;

    [[nodiscard]] bool IsIdentifier() const override;

    [[nodiscard]] std::string GetIdentifier() const override;

private:
    std::optional<int> line_number_;
};

#endif  // SPA_STATEMENT_REFERENCE_H
