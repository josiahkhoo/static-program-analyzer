#include "boolean_select.h"

std::vector<Select::SynonymWithMaybeAttribute> BooleanSelect::GetSynonyms()
    const {
  // Always return empty for this since there are no synonyms
  return {};
}

std::unordered_set<std::string> BooleanSelect::GetResultSet(
    QResult q_result) const {
  std::unordered_set<std::string> result_set;
  if (q_result.HasBeenQueried() && q_result.GetRows().empty()) {
    // Inserts false if rows are empty and it has been queried on already
    result_set.insert("FALSE");
  } else {
    // Inserts true if rows are non-empty or it has not been queried on
    result_set.insert("TRUE");
  }
  return result_set;
}
