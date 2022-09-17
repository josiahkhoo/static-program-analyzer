#ifndef SPA_USES_S_RELATIONSHIP_H
#define SPA_USES_S_RELATIONSHIP_H

#include <unordered_set>

#include "common/entity/variable_entity.h"

class UsesSRelationship {
 public:
  explicit UsesSRelationship(int statement_number);

  void AddVariable(std::string variable_name);

  std::unordered_set<std::string> GetVariables() const;

  // Empty Storage
  void Clear();

 private:
  int statement_number_;
  std::unordered_set<std::string> variable_list_;
};

#endif  // SPA_USES_S_RELATIONSHIP_H
