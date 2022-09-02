#include "statement_reference.h"

StatementReference::StatementReference() : Reference() {}

std::optional<int> StatementReference::GetLineNumber() const {
  return line_no_;
}

bool StatementReference::IsLineNumber() const {
  return line_no_.has_value();
}

void StatementReference::SetLineNumber(const std::string& line_no) {
  line_no_ = stoi(line_no);
}
