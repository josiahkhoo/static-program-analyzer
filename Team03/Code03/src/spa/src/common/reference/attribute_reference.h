#ifndef SPA_ATTRIBUTE_REFERENCE_H
#define SPA_ATTRIBUTE_REFERENCE_H

#include "attribute.h"
#include "identifier.h"
#include "reference.h"

/// Represents a reference object for WITH attribute querying
/// "IDENT"| INTEGER | attrRef
class AttributeReference : public Reference {
 public:
  explicit AttributeReference(Identifier identifier);

  explicit AttributeReference(int number);

  explicit AttributeReference(Attribute attr);

  [[nodiscard]] bool IsLineNumber() const override;

  [[nodiscard]] int GetLineNumber() const override;

  [[nodiscard]] bool IsIdentifier() const override;

  [[nodiscard]] Identifier GetIdentifier() const override;

  [[nodiscard]] bool IsAttributeName() const;

  [[nodiscard]] Attribute::AttributeName GetAttributeName() const;

  [[nodiscard]] bool IsAttributeTypeName() const;

  [[nodiscard]] bool IsAttributeTypeInteger() const;

  [[nodiscard]] std::string GetValue() const;

 private:
  std::optional<Identifier> identifier_;
  std::optional<int> number_;
  std::optional<Attribute> attr_;
};

#endif  // SPA_ATTRIBUTE_REFERENCE_H
