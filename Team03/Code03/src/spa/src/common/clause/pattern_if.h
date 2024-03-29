#ifndef SPA_PATTERN_IF_H
#define SPA_PATTERN_IF_H

#include <vector>

#include "common/pair.h"
#include "common/query_operation.h"
#include "common/reference/entity_reference.h"

class PatternIf : public QueryOperation {
 public:
  explicit PatternIf(Synonym syn, EntityReference entity);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      QueryablePkb &queryable_pkb) override;

  [[nodiscard]] const EntityReference &GetEntity() const;

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

 private:
  Synonym syn_;
  EntityReference entity_;
};

#endif  // SPA_PATTERN_IF_H
