#include "reference.h"

Reference::Reference() { is_wild_card_ = false; }

std::optional<std::string> Reference::GetSynonym() const { return synonym_; }

bool Reference::IsSynonym() const { return synonym_.has_value(); }

bool Reference::IsWildCard() const { return is_wild_card_; }

void Reference::SetSynonym(const std::string& synonym) { synonym_ = synonym; }

void Reference::SetWildCard() { is_wild_card_ = true; }
