#include "query_string.h"

SelectClause QueryString::GetSelectClause() const {
  return select_clause_;
}

std::vector<QueryTail> QueryString::GetTails() const {
  return {};
}

void QueryString::AddSelectClause(SelectClause select_clause) {
  select_clause_ = select_clause;
}
