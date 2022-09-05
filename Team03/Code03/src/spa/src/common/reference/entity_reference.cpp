#include "entity_reference.h"

#include <cassert>
#include <utility>

EntityReference::EntityReference() : Reference(true) {}

EntityReference::EntityReference(Synonym synonym)
    : Reference(std::move(synonym)) {}

EntityReference::EntityReference(std::string identifier)
    : identifier_(identifier), Reference(false) {}

std::string EntityReference::GetIdentifier() const {
  assert(IsIdentifier());
  return identifier_.value();
}

bool EntityReference::IsIdentifier() const { return identifier_.has_value(); }

bool EntityReference::IsLineNumber() const { return false; }

int EntityReference::GetLineNumber() const {
  assert(IsLineNumber());
  return -1;
}