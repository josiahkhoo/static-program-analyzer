#include "attribute.h"

#include <utility>

Attribute::Attribute(EntityType entity_type, std::string identifier,
                     AttributeName name)
    : name_(name), Synonym(entity_type, std::move(identifier)) {}

AttributeName Attribute::GetAttributeName() const { return name_; }
