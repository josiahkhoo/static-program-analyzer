#include "query_string_builder.h"

QueryStringBuilder::QueryStringBuilder() = default;

void QueryStringBuilder::AddDeclaration(
    const EntityReference& declared_entity) {
  entities_.push_back(declared_entity);
}

void QueryStringBuilder::AddSelect(Select select_clause) {
  select_ = std::move(select_clause);
}

QueryString QueryStringBuilder::GetQueryString() {
  return QueryString(select_.value(), entities_, such_that_);
}

void QueryStringBuilder::AddSuchThat(const SuchThat& such_that) {
  such_that_.push_back(such_that);
}
