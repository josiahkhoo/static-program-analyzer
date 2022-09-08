#ifndef SPA_QUERY_STRING_H
#define SPA_QUERY_STRING_H

#include <vector>

#include "common/clause/clause.h"
#include "common/clause/follows_clause.h"
#include "common/clause/follows_t_clause.h"
#include "common/clause/pattern.h"
#include "common/clause/select.h"
#include "common/entity/entity.h"

class QueryString {
 public:
  explicit QueryString(Select select, std::vector<Synonym> declared_synonyms,
                       std::vector<std::shared_ptr<Clause>> clauses,
                       std::vector<std::shared_ptr<Pattern>> patterns);

  [[nodiscard]] Select GetSelect() const;

  [[nodiscard]] const std::vector<Synonym> &GetSynonyms() const;

  [[nodiscard]] const std::vector<std::shared_ptr<Clause>> &GetClauses() const;

  [[nodiscard]] const std::vector<std::shared_ptr<Pattern>> &GetPatterns()
      const;

 private:
  std::vector<std::shared_ptr<Clause>> clauses_;
  std::vector<std::shared_ptr<Pattern>> patterns_;
  std::vector<Synonym> declared_synonyms_;
  Select select_;
};

#endif  // SPA_QUERY_STRING_H