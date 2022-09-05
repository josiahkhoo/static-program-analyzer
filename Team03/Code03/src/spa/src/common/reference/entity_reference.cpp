#include "entity_reference.h"

#include <utility>

EntityReference::EntityReference() : Reference(true) {}

EntityReference::EntityReference(Synonym synonym)
    : Reference(std::move(synonym)) {}

std::string EntityReference::GetIdentifier() const {
  assert(IsIdentifier());
  return identifier_.value();
}

bool EntityReference::IsIdentifier() const { return identifier_.has_value(); }

EntityReference::EntityReference(std::string identifier)
    : identifier_(identifier), Reference(false) {}
