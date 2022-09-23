#include "boolean_select.h"

std::vector<Synonym> BooleanSelect::GetSynonyms() const {
  // Always return empty for this since there are no synonyms
  return {};
}

std::unordered_set<std::string> BooleanSelect::GetResultSet(
    QResult q_result) const {
  std::unordered_set<std::string> result_set;
  !q_result.GetRows().empty() ? result_set.insert("TRUE")
                              : result_set.insert("FALSE");
  return result_set;
}
