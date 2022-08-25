//
// Created by Josiah Khoo on 25/8/22.
//

#ifndef SPA_QUERYABLE_H
#define SPA_QUERYABLE_H

#include "vector"

template <class T> class Queryable {
public:
  virtual std::vector<T> query() = 0;
};

#endif // SPA_QUERYABLE_H
