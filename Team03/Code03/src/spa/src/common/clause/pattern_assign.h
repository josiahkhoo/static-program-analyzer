#ifndef SPA_PATTERN_ASSIGN_H
#define SPA_PATTERN_ASSIGN_H

#include <vector>

#include "common/pair.h"
#include "common/query_operation.h"
#include "common/reference/entity_reference.h"
#include "common/reference/expression.h"

class PatternAssign : public QueryOperation {
 public:
  explicit PatternAssign(Synonym syn, EntityReference entity,
                         Expression expression);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      QueryablePkb &queryable_pkb) override;

  [[nodiscard]] const EntityReference &GetEntity() const;

  [[nodiscard]] const Expression &GetExpression() const;

  [[nodiscard]] Synonym GetSynonym() const override;

  [[nodiscard]] std::pair<Synonym, Synonym> GetSynonymPair() const override;

  [[nodiscard]] Type GetType() const override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, QueryablePkb &queryable_pkb) override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, QueryablePkb &queryable_pkb) override;

  [[nodiscard]] IterateSide GetIterateSide(
      std::vector<std::vector<std::string>> lhs,
      std::vector<std::vector<std::string>> rhs) const override;

  [[nodiscard]] bool IsTrue(QueryablePkb &queryable_pkb) override;
  Speed GetSpeed() const override;

 private:
  Synonym syn_;
  EntityReference entity_;
  Expression expression_;
};

#endif  // SPA_PATTERN_ASSIGN_H
