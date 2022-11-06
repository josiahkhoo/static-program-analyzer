#include "pkb.h"

PKB::PKB()
    : storable_pkb_impl_(StorablePkbImpl(entity_manager_, relationship_manager_,
                                         pattern_manager_)),
      queryable_pkb_impl_(QueryablePkbImpl(
          entity_manager_, relationship_manager_, pattern_manager_)) {}

StorablePkbImpl& PKB::GetStorablePkbImpl() { return storable_pkb_impl_; }

QueryablePkbImpl& PKB::GetQueryablePkbImpl() { return queryable_pkb_impl_; }
