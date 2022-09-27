#include "attribute_reference.h"

#include <cassert>
#include <utility>

// TODO: Name Mapper

AttributeReference::AttributeReference(std::string identifier)
    : identifier_(identifier), Reference(false) {}

AttributeReference::AttributeReference(int number)
    : number_(number), Reference(false) {}

AttributeReference::AttributeReference(Synonym syn, AttributeName name)
    : name_(name), Reference(std::move(syn)) {}

bool AttributeReference::IsLineNumber() const { return number_.has_value(); }

int AttributeReference::GetLineNumber() const {
  assert(IsLineNumber());
  return number_.value();
}

bool AttributeReference::IsIdentifier() const {
  return identifier_.has_value();
}

std::string AttributeReference::GetIdentifier() const {
  assert(IsIdentifier());
  return identifier_.value();
}

bool AttributeReference::IsAttributeName() const { return name_.has_value(); }

std::string AttributeReference::GetAttributeName() const {
  assert(IsAttributeName());
  return "name_.value()";
}
