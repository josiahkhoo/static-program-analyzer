#include "query_string.h"

#include <utility>

QueryString::QueryString(Select select, std::vector<Synonym> synonyms,
                         std::vector<std::shared_ptr<Clause>> clauses,
                         std::vector<std::shared_ptr<Pattern>> patterns)
    : select_(std::move(select)),
      declared_synonyms_(std::move(synonyms)),
      patterns_(std::move(patterns)),
      clauses_(std::move(clauses)) {}

Select QueryString::GetSelect() const { return select_; }

const std::vector<Synonym> &QueryString::GetSynonyms() const {
  return declared_synonyms_;
}

const std::vector<std::shared_ptr<Clause>> &QueryString::GetClauses() const {
  return clauses_;
}

const std::vector<std::shared_ptr<Pattern>> &QueryString::GetPatterns() const {
  return patterns_;
}
