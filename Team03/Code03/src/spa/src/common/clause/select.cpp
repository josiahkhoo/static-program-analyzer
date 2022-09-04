#include "select.h"

#include <utility>

Select::Select(EntityReference entity) : entity_(std::move(entity)) {}

const EntityReference& Select::GetEntity() const { return entity_; }
