#ifndef SPA_PKB_H
#define SPA_PKB_H

#include "pkb/impl/queryable_pkb_impl.h"
#include "pkb/impl/storable_pkb_impl.h"

class PKB {
 public:
  PKB();

  [[nodiscard]] StorablePkbImpl& GetStorablePkbImpl();

  [[nodiscard]] QueryablePkbImpl& GetQueryablePkbImpl();

 private:
  EntityManager entity_manager_;
  RelationshipManager relationship_manager_;
  PatternManager pattern_manager_;
  StorablePkbImpl storable_pkb_impl_;
  QueryablePkbImpl queryable_pkb_impl_;
};

#endif  // SPA_PKB_H
