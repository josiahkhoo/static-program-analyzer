#include "attribute_reference.h"

#include <cassert>
#include <utility>

AttributeReference::AttributeReference(Identifier identifier)
    : identifier_(identifier), Reference(false) {}

AttributeReference::AttributeReference(int number)
    : number_(number), Reference(false) {}

AttributeReference::AttributeReference(Attribute attr)
    : attr_(attr), Reference(attr.GetSynonym()) {}

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

bool AttributeReference::IsAttributeName() const { return attr_.has_value(); }

AttributeName AttributeReference::GetAttributeName() const {
  assert(IsAttributeName());
  return attr_.value().GetAttributeName();
}

std::string AttributeReference::GetValue() const {
  if (IsIdentifier())
    return GetIdentifier();
  else if (IsLineNumber())
    return std::to_string(GetLineNumber());
  else {
    assert(false);
    return "";
  }
}
