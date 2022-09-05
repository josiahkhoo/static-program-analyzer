#include "select.h"

#include <utility>

Select::Select(Synonym synonym) : synonym_(std::move(synonym)) {}

const Synonym& Select::GetSynonym() const { return synonym_; }
