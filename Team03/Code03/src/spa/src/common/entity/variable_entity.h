#ifndef SPA_VARIABLE_ENTITY_H
#define SPA_VARIABLE_ENTITY_H

#include "entity.h"

class VariableEntity : public Entity {
public:
    explicit VariableEntity(const TNode &node, std::string name);

    [[nodiscard]] std::string GetName() const;

private:
    std::string name_;
};

#endif  // SPA_VARIABLE_ENTITY_H
