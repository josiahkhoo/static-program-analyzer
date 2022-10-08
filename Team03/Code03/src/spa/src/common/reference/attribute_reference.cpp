#include "attribute_reference.h"

#include <cassert>

#include "common/reference/attribute_name.h"

AttributeReference::AttributeReference(Identifier identifier)
    : identifier_(identifier), Reference(false) {}

AttributeReference::AttributeReference(Integer number)
    : number_(number), Reference(false) {}

AttributeReference::AttributeReference(Attribute attr)
    : attr_(attr), Reference(attr.GetSynonym()) {}

bool AttributeReference::IsLineNumber() const { return number_.has_value(); }

Integer AttributeReference::GetLineNumber() const {
  assert(IsLineNumber());
  return number_.value();
}

bool AttributeReference::IsIdentifier() const {
  return identifier_.has_value();
}

Identifier AttributeReference::GetIdentifier() const {
  assert(IsIdentifier());
  return identifier_.value();
}

bool AttributeReference::IsAttributeName() const { return attr_.has_value(); }

AttributeName AttributeReference::GetAttributeName() const {
  assert(IsAttributeName());
  return attr_.value().GetAttributeName();
}

bool AttributeReference::IsAttributeTypeName() const {
  assert(IsAttributeName());
  return attr_.value().IsName();
}

bool AttributeReference::IsAttributeTypeInteger() const {
  assert(IsAttributeName());
  return attr_.value().IsInteger();
}

Identifier AttributeReference::GetValue() const {
  if (IsIdentifier())
    return GetIdentifier();
  else if (IsLineNumber())
    return std::to_string(GetLineNumber());
  else {
    assert(false);
    return "";
  }
}
