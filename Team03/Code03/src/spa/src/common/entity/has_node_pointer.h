#ifndef SPA_HAS_NODE_POINTER_H
#define SPA_HAS_NODE_POINTER_H

#include "common/t_node.h"

class HasNodePointer {
 public:
  virtual const TNode* GetNodePointer() const = 0;
};

#endif  // SPA_HAS_NODE_POINTER_H
