#ifndef SPA_PROCEDURE_ENTITY_H
#define SPA_PROCEDURE_ENTITY_H

#include "entity.h"

class ProcedureEntity : public Entity {
public:
    explicit ProcedureEntity(const TNode &node, std::string name);

    [[nodiscard]] std::string GetName() const;

private:
    std::string name_;
};

#endif  // SPA_PROCEDURE_ENTITY_H
