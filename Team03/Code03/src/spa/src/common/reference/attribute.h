#ifndef SPA_ATTRIBUTE_H
#define SPA_ATTRIBUTE_H

#include <unordered_map>

#include "common/reference/attribute_name.h"
#include "synonym.h"

class Attribute {
 public:
  static std::unordered_map<std::string, AttributeName> attrName_representation;

  Attribute(Synonym syn, AttributeName name);

  [[nodiscard]] Synonym GetSynonym() const;

  [[nodiscard]] AttributeName GetAttributeName() const;

  [[nodiscard]] bool IsName() const;

  [[nodiscard]] bool IsInteger() const;

 private:
  Synonym syn_;
  AttributeName name_;
};

#endif  // SPA_ATTRIBUTE_H
