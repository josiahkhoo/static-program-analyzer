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
    const QResult& q_result, const QueryablePkb& pkb) const {
  std::vector<Synonym> synonyms;
  std::transform(
      synonyms_.begin(), synonyms_.end(), std::back_inserter(synonyms),
      [](const SynonymWithMaybeAttribute& syn) { return syn.synonym; });
  std::vector<std::vector<std::string>> rows = q_result.GetRows(synonyms);
  // Check if its an attribute is needed instead of the syn itself
  for (int i = 0; i < (int)synonyms_.size(); i++) {
    auto syn = synonyms_[i];
    if (syn.maybe_attribute.has_value()) {
      auto attribute = syn.maybe_attribute.value();
      if (syn.synonym.IsValueNotEqualToAttribute(attribute)) {
        std::transform(rows.begin(), rows.end(), rows.begin(),
                       [&syn, &i, &pkb](std::vector<std::string>& row) {
                         // Replace entry in row with attribute
                         row[i] = pkb.QueryWithAttributeFromStatement(
                             syn.synonym.GetEntityType(), stoi(row[i]));
                         return row;
                       });
      }
    }
  }
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
