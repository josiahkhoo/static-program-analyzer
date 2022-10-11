#ifndef SPA_CALLS_STORAGE_H
#define SPA_CALLS_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/abstraction/calls_abstraction.h"
#include "common/abstraction/calls_t_abstraction.h"

class CallsStorage {
 public:
  void AddRelationship(CallsAbstraction abstraction);

  void AddRelationship(CallsTAbstraction abstraction);

  std::unordered_set<std::string> GetCallsProcedures() const;

  std::unordered_set<std::string> GetCallsProcedures(
      std::string proc_name) const;

  std::unordered_set<std::string> GetCallsTProcedures(
      std::string proc_name) const;

  std::unordered_set<std::string> GetCallsByProcedures(
      std::string proc_name) const;

  std::unordered_set<std::string> GetCallsByProcedures() const;

  std::unordered_set<std::string> GetCallsTByProcedures(
      std::string proc_name) const;

 private:
  std::unordered_map<std::string, std::unordered_set<std::string>> calls_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      calls_by_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>> calls_t_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      calls_t_by_map_;
};

#endif  // SPA_CALLS_STORAGE_H
