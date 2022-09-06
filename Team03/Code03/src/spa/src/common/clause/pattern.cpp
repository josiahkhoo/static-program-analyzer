#include "pattern.h"

#include <utility>

Pattern::Pattern(EntityReference entity, Expression expression)
    : entity_(std::move(entity)), expression_(std::move(expression)) {}

const EntityReference &Pattern::GetEntity() const { return entity_; }

const Expression &Pattern::GetExpression() const { return expression_; }