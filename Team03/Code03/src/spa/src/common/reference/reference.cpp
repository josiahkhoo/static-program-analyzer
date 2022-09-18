#include "reference.h"

#include <cassert>

Synonym Reference::GetSynonym() const {
  assert(synonym_.has_value());
  return synonym_.value();
}

bool Reference::IsSynonym() const { return synonym_.has_value(); }

bool Reference::IsWildCard() const { return is_wild_card_; }

bool Reference::IsEntityType(EntityType type) const {
  return synonym_->IsEntityType(type);
}

Reference::Reference(Synonym synonym) : synonym_(synonym) {
  is_wild_card_ = false;
}

Reference::Reference(bool is_wild_card) : is_wild_card_(is_wild_card) {}

bool Reference::operator==(const Reference &rhs) const {
  return synonym_ == rhs.synonym_ && is_wild_card_ == rhs.is_wild_card_;
}

bool Reference::operator!=(const Reference &rhs) const {
  return !(rhs == *this);
}
