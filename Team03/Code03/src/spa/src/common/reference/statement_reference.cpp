#include "statement_reference.h"

#include <cassert>
#include <utility>

StatementReference::StatementReference() : Reference(true) {}

StatementReference::StatementReference(Synonym synonym)
    : Reference(std::move(synonym)) {}

int StatementReference::GetLineNumber() const {
  assert(IsLineNumber());
  return line_number_.value();
}

bool StatementReference::IsLineNumber() const {
  return line_number_.has_value();
}

StatementReference::StatementReference(int line_number)
    : line_number_(line_number), Reference(false) {}

bool StatementReference::IsIdentifier() const { return false; }

std::string StatementReference::GetIdentifier() const {
  assert(IsIdentifier());
  return "";
}
