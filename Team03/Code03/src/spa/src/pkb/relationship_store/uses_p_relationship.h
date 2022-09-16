#ifndef SPA_USES_P_RELATIONSHIP_H
#define SPA_USES_P_RELATIONSHIP_H

#include <unordered_set>
#include "common/entity/variable_entity.h"

class UsesPRelationship {
 public:
  explicit UsesPRelationship(std::string procedure_name);

  void AddVariable(VariableEntity variable);

  std::unordered_set<std::string> GetVariables() const;

 private:
  std::string procedure_name_;
  std::unordered_set<std::string> variable_list_;
};

#endif  // SPA_USES_P_RELATIONSHIP_H
