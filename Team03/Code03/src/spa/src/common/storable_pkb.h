#ifndef SPA_STORABLE_PKB_H
#define SPA_STORABLE_PKB_H

#include <vector>

template <class T>
class StorablePkb {
 public:
  virtual void Store(std::vector<T> storables) = 0;
};

#endif  // SPA_STORABLE_PKB_H
