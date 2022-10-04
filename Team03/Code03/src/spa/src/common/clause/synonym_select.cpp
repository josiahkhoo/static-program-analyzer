#include "synonym_select.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>

SynonymSelect::SynonymSelect(std::vector<SynonymWithMaybeAttribute> synonyms)
    : synonyms_(std::move(synonyms)) {}

std::vector<Select::SynonymWithMaybeAttribute> SynonymSelect::GetSynonyms()
    const {
  return synonyms_;
}

std::unordered_set<std::string> SynonymSelect::GetResultSet(
    QResult q_result) const {
  auto retrieve_first_op = [](const SynonymWithMaybeAttribute& syn) {
    return syn.synonym;
  };
  std::vector<Synonym> synonyms;
  std::transform(synonyms_.begin(), synonyms_.end(),
                 std::back_inserter(synonyms), retrieve_first_op);
  std::vector<std::vector<std::string>> rows = q_result.GetRows(synonyms);
  std::unordered_set<std::string> result_set;
  for (auto row : rows) {
    // Concat inside of rows with space
    if (!row.empty())
      result_set.insert(std::accumulate(
          ++row.begin(), row.end(), *row.begin(),
          [](auto& a, auto& b) { return a.append(" ").append(b); }));
  }
  return result_set;
}
