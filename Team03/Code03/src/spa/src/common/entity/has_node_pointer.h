#ifndef SPA_HAS_NODE_POINTER_H
#define SPA_HAS_NODE_POINTER_H

#include "common/t_node.h"

class HasNodePointer {
 public:
  /// Retrieves a node pointer associated with the implemented class.
  /// \return Node pointer.
  [[nodiscard]] virtual const TNode *GetNodePointer() const = 0;
};

#endif  // SPA_HAS_NODE_POINTER_H
