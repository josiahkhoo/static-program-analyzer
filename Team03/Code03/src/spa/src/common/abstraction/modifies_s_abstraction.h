//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_MODIFIES_S_ABSTRACTION_H
#define SPA_MODIFIES_S_ABSTRACTION_H


#include "common/entity/statement_entity.h"
#include "abstraction.h"

class ModifiesSAbstraction : public Abstraction<StatementRef, Entity> {
public:
    const StatementEntity &getLeftHandSide() override;

    const Entity &getRightHandSide() override;
};


#endif //SPA_MODIFIES_S_ABSTRACTION_H
