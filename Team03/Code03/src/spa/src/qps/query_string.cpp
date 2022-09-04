#include "query_string.h"

#include <utility>

QueryString::QueryString(Select select, std::vector<EntityReference> entities,
                         std::vector<Clause> clauses)
    : select_(std::move(select)),
      entities_(std::move(entities)),
      clauses_(clauses) {}

Select QueryString::GetSelect() const { return select_; }

const std::vector<EntityReference>& QueryString::GetEntities() const {
  return entities_;
}

const std::vector<Clause>& QueryString::GetClause() const { return clauses_; }
