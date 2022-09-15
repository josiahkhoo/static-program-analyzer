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

void QueryStringBuilder::AddQueryOperation(
    const std::shared_ptr<QueryOperation>& query_operation) {
  query_operations_.reserve(1);
  query_operations_.emplace_back(query_operation);
}

QueryString QueryStringBuilder::GetQueryString() {
  return QueryString(select_.value(), declared_synonyms_, query_operations_);
}

Synonym QueryStringBuilder::GetSynonym(const std::string& identifier) const {
  for (auto synonym : declared_synonyms_) {
    if (synonym.GetIdentifier() == identifier) {
      return synonym;
    }
  }
  throw std::runtime_error("Cannot find synonym matching given identifier");
}

bool QueryStringBuilder::IsOperationsEmpty() {
  return query_operations_.empty();
}

bool QueryStringBuilder::IsDeclarationsEmpty() {
  return declared_synonyms_.empty();
}