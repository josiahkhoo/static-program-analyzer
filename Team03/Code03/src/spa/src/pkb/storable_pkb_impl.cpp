//
// Created by kohha on 3/11/2022.
//

#include "storable_pkb_impl.h"

template <class T, class U, class V>
void StorablePkbImpl<T, U, V>::Store(std::vector<Entity> ts) {
  entity_storable_pkb_.Store(ts);
}

template <class T, class U, class V>
void StorablePkbImpl<T, U, V>::Store(std::vector<Abstraction<U, V>> ts) {
  abstraction_storable_pkb_.Store(ts);
}
