#include "statement_entity.h"

StatementEntity::StatementEntity(int line_number) : line_number_(line_number) {}

int StatementEntity::GetLineNumber() const { return line_number_; }

std::string StatementEntity::ToString() const {
  return std::to_string(line_number_);
}