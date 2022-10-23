#include "affects_statement_checker.h"

#include "common/clause/affects_clause.h"
#include "qps/exceptions/semantic_exception.h"

AffectsStatementChecker::AffectsStatementChecker() = default;

void AffectsStatementChecker::Check(const QueryString &q_string,
                                    const QueryablePkb &queryable_pkb) {
  for (const auto &query_operation : q_string.GetQueryOperation()) {
    if (AffectsStatementChecker:: instanceof
        <AffectsClause>(query_operation.get())) {
      auto *affCl = dynamic_cast<AffectsClause *>(query_operation.get());
      if (affCl->GetLeftHandSide().IsLineNumber()) {
        if (!queryable_pkb.CheckValidAffectsStmtNo(
                affCl->GetLeftHandSide().GetLineNumber())) {
          throw SemanticException("Invalid Affects clause statement number");
        }
      }
      if (affCl->GetRightHandSide().IsLineNumber()) {
        if (!queryable_pkb.CheckValidAffectsStmtNo(
                affCl->GetRightHandSide().GetLineNumber())) {
          throw SemanticException("Invalid Affects clause statement number");
        }
      }
    }
  }
}
