#include "entity_reference.h"

#include <cassert>
#include <utility>

#include "integer.h"

EntityReference::EntityReference() : Reference(true) {}

EntityReference::EntityReference(Synonym synonym)
    : Reference(std::move(synonym)) {}

EntityReference::EntityReference(Identifier identifier)
    : Reference(false), identifier_(identifier) {}

Identifier EntityReference::GetIdentifier() const {
  assert(IsIdentifier());
  return identifier_.value();
}

bool EntityReference::IsIdentifier() const { return identifier_.has_value(); }

bool EntityReference::IsLineNumber() const { return false; }

Integer EntityReference::GetLineNumber() const {
  assert(IsLineNumber());
  return -1;
}