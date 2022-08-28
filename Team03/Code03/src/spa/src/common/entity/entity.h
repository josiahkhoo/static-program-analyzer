#ifndef SPA_ENTITY_H
#define SPA_ENTITY_H

#include "has_node_pointer.h"

class Entity : public HasNodePointer {
 public:
  explicit Entity(const TNode &node);
  [[nodiscard]] const TNode *GetNodePointer() const;

 private:
  const TNode &node_;
};

#endif  // SPA_ENTITY_H
