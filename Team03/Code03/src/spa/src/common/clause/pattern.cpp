#include "pattern.h"

Pattern::Pattern(EntityReference entity, std::string expression)
    : entity_(entity), expression_(expression) {}

const EntityReference& Pattern::GetEntity() const {
  return entity_;
}

const std::string& Pattern::GetExpression() const {
  return expression_;
}
