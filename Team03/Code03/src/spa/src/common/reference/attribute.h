#ifndef SPA_ATTRIBUTE_H
#define SPA_ATTRIBUTE_H

#include "synonym.h"

enum AttributeName {
  PROC_NAME,
  VAR_NAME,
  VALUE,
  STMT_NO,
};

class Attribute : public Synonym {
 public:
  Attribute(EntityType entity_type, std::string identifier, AttributeName name);

  [[nodiscard]] AttributeName GetAttributeName() const;

 private:
  AttributeName name_;
};

#endif  // SPA_ATTRIBUTE_H
