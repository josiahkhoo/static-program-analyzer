#ifndef SPA_ABSTRACTION_H
#define SPA_ABSTRACTION_H

#include "common/pair.h"
#include "common/storable.h"

template <class T, class U>
class Abstraction : Pair<T, U>, Storable {
 public:
  virtual ~Abstraction() = default;
};

#endif  // SPA_ABSTRACTION_H
