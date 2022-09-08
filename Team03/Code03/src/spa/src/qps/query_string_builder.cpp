#include "query_string_builder.h"

#include <stdexcept>

QueryStringBuilder::QueryStringBuilder() = default;

void QueryStringBuilder::AddDeclaration(const Synonym& declared_synonym) {
  declared_synonyms_.reserve(1);
  declared_synonyms_.push_back(declared_synonym);
}

void QueryStringBuilder::AddSelect(Select select_clause) {
  select_ = std::move(select_clause);
}

void QueryStringBuilder::AddClause(const std::shared_ptr<Clause>& such_that) {
  clauses_.reserve(1);
  clauses_.emplace_back(such_that);
}

QueryString QueryStringBuilder::GetQueryString() {
  return QueryString(select_.value(), declared_synonyms_, clauses_, patterns_);
}

Synonym QueryStringBuilder::GetSynonym(const std::string& identifier) const {
  for (auto synonym : declared_synonyms_) {
    if (synonym.GetIdentifier() == identifier) {
      return synonym;
    }
  }
  throw std::runtime_error("Cannot find synonym matching given identifier");
}

void QueryStringBuilder::AddPattern(const std::shared_ptr<Pattern>& pattern) {
  patterns_.push_back(pattern);
}

bool QueryStringBuilder::IsClauseEmpty() { return clauses_.empty(); }
