//
// Created by kohha on 3/11/2022.
//

#include "storable_pkb_impl.h"

StorablePkbImpl::StorablePkbImpl() = default;

EntityStorablePkb StorablePkbImpl::GetEntityStorablePkb() const {
  return entity_storable_pkb_;
}

AbstractionStorablePkb StorablePkbImpl::GetAbstractionStorablePkb() const {
  return abstraction_storable_pkb_;
}
