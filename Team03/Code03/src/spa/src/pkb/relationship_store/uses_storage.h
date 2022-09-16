#ifndef SPA_USES_STORAGE_H
#define SPA_USES_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "uses_by_relationship.h"
#include "uses_relationship.h"

class UsesStorage {
 public:
  void AddRelationship(UsesPAbstraction abstraction);

  void AddRelationship(UsesSAbstraction abstraction);

  std::unordered_set<std::string> GetUsesP() const;

  std::unordered_set<std::string> GetUsesP(std::string uses_name) const;

  std::unordered_set<std::string> GetUsesPBy() const;

  std::unordered_set<std::string> GetUsesPBy(std::string variable_name) const;

  std::unordered_set<std::string> GetUsesS() const;

  std::unordered_set<std::string> GetUsesS(std::string uses_name) const;

  std::unordered_set<std::string> GetUsesSBy() const;

  std::unordered_set<std::string> GetUsesSBy(std::string variable_name) const;

  // Empty storage
  void Clear();

 private:
  std::unordered_map<std::string, std::unique_ptr<UsesRelationship>>
      uses_p_map_;
  std::unordered_map<std::string, std::unique_ptr<UsesByRelationship>>
      uses_p_by_map_;
  std::unordered_map<std::string, std::unique_ptr<UsesRelationship>>
      uses_s_map_;
  std::unordered_map<std::string, std::unique_ptr<UsesByRelationship>>
      uses_s_by_map_;
};

#endif  // SPA_USES_STORAGE_H
