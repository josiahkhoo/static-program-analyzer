#include "query_string.h"

#include <utility>

QueryString::QueryString(Select select, std::vector<Synonym> synonyms,
                         std::vector<std::shared_ptr<Clause>> clauses)
        : select_(std::move(select)),
          declared_synonyms_(std::move(synonyms)),
          clauses_(std::move(clauses)) {}

Select QueryString::GetSelect() const { return select_; }

const std::vector<Synonym> &QueryString::GetSynonyms() const {
    return declared_synonyms_;
}

const std::vector<std::shared_ptr<Clause>> &QueryString::GetClauses() const {
    return clauses_;
}
