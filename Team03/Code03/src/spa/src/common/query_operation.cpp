#include "common/query_operation.h"

bool QueryOperation::IsRelatedTo(std::unordered_set<Synonym> synonyms) const {
  switch (this->GetType()) {
    case DOUBLE_SYNONYM:
      return synonyms.count(this->GetSynonymPair().first) ||
             synonyms.count(this->GetSynonymPair().second);
    case SINGLE_SYNONYM:
      return synonyms.count(this->GetSynonym());
    case NO_SYNONYM:
    default:
      return false;
  }
}

QueryOperation::Speed QueryOperation::GetSpeed() const {
  return QueryOperation::DEFAULT;
}

std::vector<Synonym> QueryOperation::GetSynonyms() const {
  switch (this->GetType()) {
    case DOUBLE_SYNONYM:
      return {this->GetSynonymPair().first, this->GetSynonymPair().second};
    case SINGLE_SYNONYM:
      return {this->GetSynonym()};
    case NO_SYNONYM:
    default:
      return {};
  }
}