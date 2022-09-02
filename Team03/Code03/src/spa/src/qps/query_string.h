#ifndef SPA_QUERY_STRING_H
#define SPA_QUERY_STRING_H

#include <vector>

#include "query_tail.h"
#include "select_clause.h"

class QueryString {
 public:
  [[nodiscard]] SelectClause GetSelectClause() const;
  [[nodiscard]] std::vector<QueryTail> GetTails() const;
  void AddSelectClause(SelectClause select_clause);
 private:
  SelectClause select_clause_;
};

#endif  // SPA_QUERY_STRING_H