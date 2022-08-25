//
// Created by Josiah Khoo on 25/8/22.
//

#ifndef SPA_STORABLE_H
#define SPA_STORABLE_H

#include "vector"

template <class T>
class Storable {
 public:
  virtual void store(std::vector<T> ts) = 0;
};

#endif  // SPA_STORABLE_H
