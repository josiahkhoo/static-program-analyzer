#ifndef SPA_ASSIGN_ENTITY_H
#define SPA_ASSIGN_ENTITY_H

#include "entity.h"
#include "statement_entity.h"

class AssignEntity : public StatementEntity {
public:
    explicit AssignEntity(const TNode &node, int line_number);
};

#endif  // SPA_ASSIGN_ENTITY_H
