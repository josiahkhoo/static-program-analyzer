#ifndef SPA_USES_RELATIONSHIP_H
#define SPA_USES_RELATIONSHIP_H

#include <string>
#include <unordered_set>

class UsesRelationship {
 public:
  explicit UsesRelationship(std::string uses_name);

  void AddVariable(std::string variable_name);

  std::unordered_set<std::string> GetVariables() const;

  // Empty Storage
  void Clear();

 private:
  std::string uses_name_;
  std::unordered_set<std::string> variable_list_;
};

#endif  // SPA_USES_RELATIONSHIP_H
