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
  explicit QueryString(
      Select select, std::vector<Synonym> declared_synonyms,
      std::vector<std::shared_ptr<QueryOperation>> query_operations);

  [[nodiscard]] Select GetSelect() const;

  [[nodiscard]] const std::vector<Synonym> &GetSynonyms() const;

  [[nodiscard]] std::vector<std::shared_ptr<QueryOperation>> GetQueryOperation()
      const;

 private:
  std::vector<std::shared_ptr<QueryOperation>> query_operations_;
  std::vector<Synonym> declared_synonyms_;
  Select select_;
};

#endif  // SPA_QUERY_STRING_H