#include "query_string_builder.h"

#include <stdexcept>

QueryStringBuilder::QueryStringBuilder() = default;

void QueryStringBuilder::AddDeclaration(const Synonym &declared_synonym) {
  declared_synonyms_.push_back(declared_synonym);
}

void QueryStringBuilder::AddSelect(Select select_clause) {
  select_ = std::move(select_clause);
}

// Todo: Validate entity referenced exist in declaration_entities
QueryString QueryStringBuilder::GetQueryString() {
  return QueryString(select_.value(), declared_synonyms_, such_that_);
}

void QueryStringBuilder::AddClause(std::shared_ptr<Clause> such_that) {
  such_that_.push_back(such_that);
}

Synonym QueryStringBuilder::GetSynonym(const std::string &identifier) const {
  for (auto synonym : declared_synonyms_) {
    if (synonym.GetIdentifier() == identifier) {
      return synonym;
    }
  }
  throw std::runtime_error("Cannot find synonym matching given identifier");
}
