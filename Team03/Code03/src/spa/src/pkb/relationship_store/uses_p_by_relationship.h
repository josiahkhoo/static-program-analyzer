#ifndef SPA_USES_P_BY_RELATIONSHIP_H
#define SPA_USES_P_BY_RELATIONSHIP_H

#include <string>
#include <unordered_set>

class UsesPByRelationship {
 public:
  explicit UsesPByRelationship(std::string variable_name);

  void AddProcedure(std::string procedure_name);

  std::unordered_set<std::string> GetUses() const;

  // Empty Storage
  void Clear();

 private:
  std::string variable_name_;
  std::unordered_set<std::string> procedure_list_;
};

#endif  // SPA_USES_P_BY_RELATIONSHIP_H
