#ifndef SPA_USES_S_BY_RELATIONSHIP_H
#define SPA_USES_S_BY_RELATIONSHIP_H

#include <string>
#include <unordered_set>

class UsesSByRelationship {
 public:
  explicit UsesSByRelationship(std::string variable_name);

  void AddStatement(int statement_number);

  std::unordered_set<int> GetUses() const;

  // Empty Storage
  void Clear();

 private:
  std::string variable_name_;
  std::unordered_set<int> statement_list_;
};

#endif  // SPA_USES_S_BY_RELATIONSHIP_H
