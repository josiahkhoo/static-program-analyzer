#ifndef SPA_PARENT_CLAUSE_H
#define SPA_PARENT_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class ParentClause : public Clause {
 public:
  ParentClause(StatementReference lhs, StatementReference rhs);

  [[nodiscard]] std::map<std::string, std::unordered_set<std::string>> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // SPA_PARENT_CLAUSE_H
