#ifndef SPA_QUERY_STRING_BUILDER_H
#define SPA_QUERY_STRING_BUILDER_H

#include "common/clause/follows_clause.h"
#include "common/clause/follows_t_clause.h"
#include "common/clause/pattern.h"
#include "common/clause/select.h"
#include "common/entity/entity.h"
#include "query_string.h"

class QueryStringBuilder {
 public:
  QueryStringBuilder();

  void AddDeclaration(const Synonym& declared_synonym);

  void AddSelect(const std::shared_ptr<Select>& select_clause);

  void AddQueryOperation(
      const std::shared_ptr<QueryOperation>& query_operation);

  QueryString GetQueryString();

  [[nodiscard]] Synonym GetSynonym(const std::string& identifier) const;

  bool IsOperationsEmpty();

  bool IsDeclarationsEmpty();

 private:
  std::vector<Synonym> declared_synonyms_;
  std::vector<std::shared_ptr<QueryOperation>> query_operations_;
  std::optional<std::shared_ptr<Select>> select_;
};

#endif  // SPA_QUERY_STRING_BUILDER_H
