#ifndef SPA_USES_S_RELATIONSHIP_H
#define SPA_USES_S_RELATIONSHIP_H

#include <unordered_set>

#include "common/entity/variable_entity.h"

class UsesSRelationship {
 public:
  explicit UsesSRelationship(std::string statement_number);

  void AddVariable(VariableEntity variable);

  std::unordered_set<std::string> GetVariables() const;

  // Empty Storage
  void Clear();

 private:
  std::string statement_number_;
  std::unordered_set<std::string> variable_list_;
};

#endif  // SPA_USES_S_RELATIONSHIP_H
