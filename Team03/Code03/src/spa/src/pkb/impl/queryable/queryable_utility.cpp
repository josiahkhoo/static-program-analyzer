#include "queryable_utility.h"

/// FindIntersect
/// \param statements Statements from relationship manager
/// \param typed_statements Statements from entity manager
/// \return Statements that are in both sets of statements
std::unordered_set<std::string> QueryableUtility::FindIntersect(
    std::unordered_set<std::string> statements,
    std::unordered_set<std::string> typed_statements) {
  std::unordered_set<std::string> result;
  for (const std::string &statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}