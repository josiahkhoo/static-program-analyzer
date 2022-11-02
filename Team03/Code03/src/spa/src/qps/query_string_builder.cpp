#include "query_string_builder.h"

#include <stdexcept>

#include "qps/exceptions/semantic_exception.h"

QueryStringBuilder::QueryStringBuilder() = default;

void QueryStringBuilder::AddDeclaration(const Synonym& declared_synonym) {
  declared_synonyms_.emplace(
      std::make_pair(declared_synonym.GetIdentifier(), declared_synonym));
}

void QueryStringBuilder::AddSelect(
    const std::shared_ptr<Select>& select_clause) {
  select_ = select_clause;
}

void QueryStringBuilder::AddQueryOperation(
    const std::shared_ptr<QueryOperation>& query_operation) {
  query_operations_.reserve(1);
  query_operations_.emplace_back(query_operation);
}

QueryString QueryStringBuilder::GetQueryString() {
  std::vector<Synonym> synonyms;
  synonyms.reserve(declared_synonyms_.size());
  for (const auto& syn : declared_synonyms_) {
    synonyms.push_back(syn.second);
  }
  if (!select_.has_value()) {
    return {};
  }
  return QueryString(select_.value(), synonyms, query_operations_);
}

std::optional<Synonym> QueryStringBuilder::GetSynonym(
    const std::string& identifier) const {
  auto synonym = declared_synonyms_.find(identifier);
  if (synonym != declared_synonyms_.end()) {
    return synonym->second;
  }
  return {};
}

bool QueryStringBuilder::IsOperationsEmpty() {
  return query_operations_.empty();
}