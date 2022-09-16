#ifndef SPA_USES_BY_RELATIONSHIP_H
#define SPA_USES_BY_RELATIONSHIP_H

#include <string>
#include <unordered_set>

class UsesByRelationship {
 public:
  explicit UsesByRelationship(std::string variable_name);

  void AddUses(std::string uses_name);

  std::unordered_set<std::string> GetUses() const;

  // Empty Storage
  void Clear();

 private:
  std::string variable_name_;
  std::unordered_set<std::string> uses_list_;
};

#endif  // SPA_USES_BY_RELATIONSHIP_H
