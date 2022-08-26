#ifndef SPA_EXTRACTOR_H
#define SPA_EXTRACTOR_H

#include "sp/t_node.h"

template <typename T>
class Extractor {
  virtual std::vector<T> extract(const TNode &ast) = 0;
};

#endif  // SPA_EXTRACTOR_H
