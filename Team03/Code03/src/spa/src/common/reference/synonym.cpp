#include "synonym.h"

#include <utility>

Synonym::Synonym(EntityType entity_type, std::string identifier)
    : entity_type_(entity_type), identifier_(std::move(identifier)) {}

EntityType Synonym::GetEntityType() { return entity_type_; }

std::string Synonym::GetIdentifier() { return identifier_; }

bool Synonym::operator==(const Synonym& rhs) const {
  return entity_type_ == rhs.entity_type_ && identifier_ == rhs.identifier_;
}

bool Synonym::operator!=(const Synonym& rhs) const { return !(rhs == *this); }
