#ifndef SPA_ENTITY_H
#define SPA_ENTITY_H

#include "has_node_pointer.h"
#include "common/storable.h"

/// Base Entity class used to wrap around a node.
class Entity : public HasNodePointer, Storable {
 public:
  /// Constructs a base entity object.
  /// \param node Node reference.
  explicit Entity(const TNode &node);

  [[nodiscard]] const TNode *GetNodePointer() const override;

  bool operator==(const Entity &rhs) const;

  bool operator!=(const Entity &rhs) const;

 protected:
  const TNode &node_;
};

#endif  // SPA_ENTITY_H
