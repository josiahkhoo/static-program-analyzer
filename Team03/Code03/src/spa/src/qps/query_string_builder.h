#ifndef SPA_QUERY_STRING_BUILDER_H
#define SPA_QUERY_STRING_BUILDER_H

#include "common/clause/follows_clause.h"
#include "common/clause/follows_t_clause.h"
#include "common/clause/select.h"
#include "common/entity/entity.h"
#include "query_string.h"

class QueryStringBuilder {
 public:
  QueryStringBuilder();
  void AddDeclaration(const EntityReference& declared_entity);
  void AddSelect(Select select_clause);
  void AddSuchThat(const SuchThat& such_that);

  QueryString GetQueryString();

 private:
  std::vector<EntityReference> entities_;
  std::vector<SuchThat> such_that_;
  std::optional<Select> select_;
};

#endif  // SPA_QUERY_STRING_BUILDER_H
