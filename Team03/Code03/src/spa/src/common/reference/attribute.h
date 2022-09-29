#ifndef SPA_ATTRIBUTE_H
#define SPA_ATTRIBUTE_H

#include <unordered_map>

#include "synonym.h"

class Attribute {
 public:
  enum AttributeName {
    PROC_NAME,
    VAR_NAME,
    VALUE,
    STMT_NO,
  };

  static std::unordered_map<std::string, AttributeName> attrName_representation;

  Attribute(Synonym syn, AttributeName name);

  [[nodiscard]] Synonym GetSynonym() const;

  [[nodiscard]] AttributeName GetAttributeName() const;

 private:
  Synonym syn_;
  AttributeName name_;
};

#endif  // SPA_ATTRIBUTE_H
