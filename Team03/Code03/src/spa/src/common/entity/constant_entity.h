#ifndef SPA_CONSTANT_ENTITY_H
#define SPA_CONSTANT_ENTITY_H

#include "entity.h"

class ConstantEntity : public Entity {
 public:
  explicit ConstantEntity(const TNode &node, int value);
  [[nodiscard]] int GetValue() const;

 private:
  int value_;
};

#endif  // SPA_CONSTANT_ENTITY_H
