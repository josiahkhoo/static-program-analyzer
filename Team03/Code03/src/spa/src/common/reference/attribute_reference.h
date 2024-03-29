#ifndef SPA_ATTRIBUTE_REFERENCE_H
#define SPA_ATTRIBUTE_REFERENCE_H

#include "attribute.h"
#include "common/reference/attribute_name.h"
#include "identifier.h"
#include "reference.h"

/// Represents a reference object for WITH attribute querying
/// "IDENT"| INTEGER | attrRef
class AttributeReference : public Reference {
 public:
  explicit AttributeReference(Identifier identifier);

  explicit AttributeReference(Integer number);

  explicit AttributeReference(Attribute attr);

  [[nodiscard]] bool IsLineNumber() const override;

  [[nodiscard]] Integer GetLineNumber() const override;

  [[nodiscard]] bool IsIdentifier() const override;

  [[nodiscard]] Identifier GetIdentifier() const override;

  [[nodiscard]] bool IsAttributeName() const;

  [[nodiscard]] AttributeName GetAttributeName() const;

  [[nodiscard]] bool IsAttributeTypeName() const;

  [[nodiscard]] bool IsAttributeTypeInteger() const;

  [[nodiscard]] Identifier GetValue() const;

 private:
  std::optional<Identifier> identifier_;
  std::optional<Integer> number_;
  std::optional<Attribute> attr_;
};

#endif  // SPA_ATTRIBUTE_REFERENCE_H
