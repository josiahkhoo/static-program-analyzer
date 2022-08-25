//
// Created by Josiah Khoo on 25/8/22.
//

#ifndef SPA_UNIQUERYABLE_H
#define SPA_UNIQUERYABLE_H

#include <vector>

template <class T, class R> class Uniqueryable {
public:
  virtual std::vector<R> query(T) = 0;
};

#endif // SPA_UNIQUERYABLE_H
