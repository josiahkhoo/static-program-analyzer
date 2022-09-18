#ifndef SPA_USES_P_RELATIONSHIP_H
#define SPA_USES_P_RELATIONSHIP_H

#include <string>
#include <unordered_set>

class UsesPRelationship {
 public:
  explicit UsesPRelationship(std::string procedure_name);

  void AddVariable(std::string variable_name);

  std::unordered_set<std::string> GetVariables() const;

  // Empty Storage
  void Clear();

 private:
  std::string procedure_name_;
  std::unordered_set<std::string> variable_list_;
};

#endif  // SPA_USES_P_RELATIONSHIP_H
