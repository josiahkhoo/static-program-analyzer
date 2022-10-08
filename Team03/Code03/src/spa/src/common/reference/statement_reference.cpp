#include "statement_reference.h"

#include <cassert>
#include <utility>

StatementReference::StatementReference() : Reference(true) {}

StatementReference::StatementReference(Integer line_number)
    : line_number_(line_number), Reference(false) {}

StatementReference::StatementReference(Synonym synonym)
    : Reference(std::move(synonym)) {}

Integer StatementReference::GetLineNumber() const {
  assert(IsLineNumber());
  return line_number_.value();
}

bool StatementReference::IsLineNumber() const {
  return line_number_.has_value();
}

bool StatementReference::IsIdentifier() const { return false; }

Identifier StatementReference::GetIdentifier() const {
  return this->GetSynonym().GetIdentifier();
}
