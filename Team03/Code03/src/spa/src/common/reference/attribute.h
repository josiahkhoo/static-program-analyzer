#ifndef SPA_ATTRIBUTE_H
#define SPA_ATTRIBUTE_H

#include "synonym.h"

enum AttributeName {
  PROC_NAME,
  VAR_NAME,
  VALUE,
  STMT_NO,
};

class Attribute {
 public:
  Attribute(Synonym syn, AttributeName name);

  [[nodiscard]] Synonym GetSynonym() const;

  [[nodiscard]] AttributeName GetAttributeName() const;

  static AttributeName RetrieveAttributeName(const std::string& name);

 private:
  Synonym syn_;
  AttributeName name_;
};

#endif  // SPA_ATTRIBUTE_H
