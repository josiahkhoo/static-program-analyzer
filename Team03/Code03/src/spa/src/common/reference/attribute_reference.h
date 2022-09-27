#ifndef SPA_ATTRIBUTE_REFERENCE_H
#define SPA_ATTRIBUTE_REFERENCE_H

#include "reference.h"

/// Represents a reference object for WITH attribute querying
/// "IDENT"| INTEGER | attrRef
class AttributeReference : public Reference {
 public:
  enum AttributeName {
    PROC_NAME,
    VAR_NAME,
    VALUE,
    STMT_NO,
  };

  explicit AttributeReference(std::string identifier);

  explicit AttributeReference(int number);

  explicit AttributeReference(Synonym syn, AttributeName name);

  [[nodiscard]] bool IsLineNumber() const override;

  [[nodiscard]] int GetLineNumber() const override;

  [[nodiscard]] bool IsIdentifier() const override;

  [[nodiscard]] std::string GetIdentifier() const override;

  [[nodiscard]] bool IsAttributeName() const;

  [[nodiscard]] std::string GetAttributeName() const;

 private:
  std::optional<std::string> identifier_;
  std::optional<AttributeName> name_;
  std::optional<int> number_;

};

#endif  // SPA_ATTRIBUTE_REFERENCE_H
