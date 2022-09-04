#include "query_string_builder.h"

QueryStringBuilder::QueryStringBuilder() = default;

void QueryStringBuilder::AddDeclaration(
    const EntityReference& declared_entity) {
  entities_.push_back(declared_entity);
}

void QueryStringBuilder::AddSelect(Select select_clause) {
  select_ = std::move(select_clause);
}

// Todo: Validate entity referenced exist in declaration_entities
QueryString QueryStringBuilder::GetQueryString() {
  return QueryString(select_.value(), entities_, such_that_);
}

void QueryStringBuilder::AddClause(const Clause& such_that) {
  such_that_.push_back(such_that);
}
