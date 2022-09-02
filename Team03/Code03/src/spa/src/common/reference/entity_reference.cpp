#include "entity_reference.h"

EntityReference::EntityReference() : Reference() {}

std::optional<std::string> EntityReference::GetIdentifier() const {
  return identifier_;
}

bool EntityReference::IsIdentifier() const {
  return identifier_.has_value();
}
void EntityReference::SetIdentifier(const std::string& identifier) {
  identifier_ = identifier;
}
