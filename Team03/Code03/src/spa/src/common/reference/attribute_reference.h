#ifndef SPA_ATTRIBUTE_REFERENCE_H
#define SPA_ATTRIBUTE_REFERENCE_H

#include "attribute.h"
#include "reference.h"

/// Represents a reference object for WITH attribute querying
/// "IDENT"| INTEGER | attrRef
class AttributeReference : public Reference {
 public:

  explicit AttributeReference(std::string identifier);

  explicit AttributeReference(int number);

  explicit AttributeReference(Attribute attr);

  [[nodiscard]] bool IsLineNumber() const override;

  [[nodiscard]] int GetLineNumber() const override;

  [[nodiscard]] bool IsIdentifier() const override;

  [[nodiscard]] std::string GetIdentifier() const override;

  [[nodiscard]] bool IsAttributeName() const;

  [[nodiscard]] AttributeName GetAttributeName() const;

  [[nodiscard]] std::string GetValue() const;

 private:
  std::optional<std::string> identifier_;
  std::optional<int> number_;
  std::optional<Attribute> attr_;
};

#endif  // SPA_ATTRIBUTE_REFERENCE_H
