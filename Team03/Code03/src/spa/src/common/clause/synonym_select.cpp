#include "synonym_select.h"

#include <numeric>
#include <utility>

SynonymSelect::SynonymSelect(std::vector<Synonym> synonyms)
    : synonyms_(std::move(synonyms)) {}

std::vector<Synonym> SynonymSelect::GetSynonyms() const { return synonyms_; }

std::unordered_set<std::string> SynonymSelect::GetResultSet(
    QResult q_result) const {
  std::vector<std::vector<std::string>> rows = q_result.GetRows(GetSynonyms());
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
