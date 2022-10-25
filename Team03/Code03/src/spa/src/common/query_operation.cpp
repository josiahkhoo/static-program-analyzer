#include "common/query_operation.h"

#include <cassert>

bool QueryOperation::IsRelatedTo(QueryOperation* other_op) const {
  if (this->GetType() == DOUBLE_SYNONYM &&
      other_op->GetType() == DOUBLE_SYNONYM) {
    return this->GetSynonymPair().first == other_op->GetSynonymPair().first ||
           this->GetSynonymPair().first == other_op->GetSynonymPair().second ||
           this->GetSynonymPair().second == other_op->GetSynonymPair().first ||
           this->GetSynonymPair().second == other_op->GetSynonymPair().second;
  }
  if (this->GetType() == DOUBLE_SYNONYM &&
      other_op->GetType() == SINGLE_SYNONYM) {
    return this->GetSynonymPair().first == other_op->GetSynonym() ||
           this->GetSynonymPair().second == other_op->GetSynonym();
  }
  if (other_op->GetType() == DOUBLE_SYNONYM &&
      this->GetType() == SINGLE_SYNONYM) {
    return other_op->GetSynonymPair().first == this->GetSynonym() ||
           other_op->GetSynonymPair().second == this->GetSynonym();
  }
  return false;
}

bool QueryOperation::IsValid(const QueryablePkb& queryable_pkb) const {
  assert(queryable_pkb.CheckValidAffectsStmtNo(1));
  return true;
}
