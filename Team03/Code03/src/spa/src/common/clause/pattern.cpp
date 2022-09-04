#include "pattern.h"

#include <utility>

Pattern::Pattern(EntityReference entity, std::string expression)
    : entity_(std::move(entity)), expression_(std::move(expression)) {}

const EntityReference& Pattern::GetEntity() const { return entity_; }

const std::string& Pattern::GetExpression() const { return expression_; }
