//
// Created by kohha on 4/11/2022.
//

#ifndef SPA_STORABLE_PKB_STRATEGY_H
#define SPA_STORABLE_PKB_STRATEGY_H

#include <vector>

template <class T>
class StorablePkbStrategy {
 public:
  virtual void Store(std::vector<T> storables) = 0;
};

#endif  // SPA_STORABLE_PKB_STRATEGY_H
