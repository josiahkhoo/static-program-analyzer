#include "query_string.h"

#include <utility>

QueryString::QueryString(
    Select select, std::vector<Synonym> synonyms,
    std::vector<std::shared_ptr<QueryOperation>> query_operations)
    : select_(std::move(select)),
      declared_synonyms_(std::move(synonyms)),
      query_operations_(std::move(query_operations)) {}

Select QueryString::GetSelect() const { return select_; }

const std::vector<Synonym> &QueryString::GetSynonyms() const {
  return declared_synonyms_;
}

std::vector<std::shared_ptr<QueryOperation>> QueryString::GetQueryOperation()
    const {
  return query_operations_;
}
