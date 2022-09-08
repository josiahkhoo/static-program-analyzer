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

  void AddDeclaration(const Synonym &declared_synonym);

  void AddSelect(Select select_clause);

  void AddClause(const std::shared_ptr<Clause>& such_that);

  void AddPattern(const std::shared_ptr<Pattern>& pattern);

  QueryString GetQueryString();

  [[nodiscard]] Synonym GetSynonym(const std::string &identifier) const;

  bool IsClauseEmpty();

 private:
  std::vector<Synonym> declared_synonyms_;
  std::vector<std::shared_ptr<Clause>> clauses_;
  std::vector<std::shared_ptr<Pattern>> patterns_;
  std::optional<Select> select_;
};

#endif  // SPA_QUERY_STRING_BUILDER_H
