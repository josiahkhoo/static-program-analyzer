#include "query_string.h"

#include <utility>

QueryString::QueryString(Select select, std::vector<EntityReference> entities,
                         std::vector<SuchThat> such_that)
    : select_(std::move(select)),
      entities_(std::move(entities)),
      such_that_(std::move(such_that)) {}

Select QueryString::GetSelect() const { return select_; }

const std::vector<EntityReference>& QueryString::GetEntities() const {
  return entities_;
}

const std::vector<SuchThat>& QueryString::GetSuchThat() const {
  return such_that_;
}
