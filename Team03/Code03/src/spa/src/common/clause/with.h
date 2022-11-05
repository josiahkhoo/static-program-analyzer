#ifndef SPA_WITH_H
#define SPA_WITH_H

#include "common/query_operation.h"
#include "common/reference/attribute_reference.h"

class With : public QueryOperation {
 public:
  explicit With(AttributeReference attRefL, AttributeReference attRefR);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      QueryablePkb& queryable_pkb) override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, QueryablePkb& queryable_pkb) override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, QueryablePkb& queryable_pkb) override;

  [[nodiscard]] Type GetType() const override;

  [[nodiscard]] Synonym GetSynonym() const override;

  [[nodiscard]] std::pair<Synonym, Synonym> GetSynonymPair() const override;

  [[nodiscard]] IterateSide GetIterateSide(
      std::vector<std::vector<std::string>> lhs,
      std::vector<std::vector<std::string>> rhs) const override;

  [[nodiscard]] bool IsTrue(QueryablePkb& queryable_pkb) override;

 private:
  AttributeReference lhs_;
  AttributeReference rhs_;

  bool IsNumber(const std::string& token) const;
};

#endif  // SPA_WITH_H
