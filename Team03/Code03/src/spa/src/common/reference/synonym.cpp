#include "synonym.h"

#include <utility>

Synonym::Synonym(EntityType entity_type, std::string identifier)
    : entity_type_(entity_type), identifier_(std::move(identifier)) {}

EntityType Synonym::GetEntityType() { return entity_type_; }

std::string Synonym::GetIdentifier() { return identifier_; }

bool Synonym::IsEntityType(EntityType type) const {
  return entity_type_ == type;
}

bool Synonym::operator==(const Synonym &rhs) const {
  return entity_type_ == rhs.entity_type_ && identifier_ == rhs.identifier_;
}

bool Synonym::operator!=(const Synonym &rhs) const { return !(rhs == *this); }

bool Synonym::IsValueEqualToAttribute(AttributeName attribute_name) const {
  if ((entity_type_ == READ || entity_type_ == PRINT) &&
      attribute_name == AttributeName::VAR_NAME) {
    return false;
  }
  if (entity_type_ == CALL && attribute_name == AttributeName::PROC_NAME) {
    return false;
  }
  return true;
}
