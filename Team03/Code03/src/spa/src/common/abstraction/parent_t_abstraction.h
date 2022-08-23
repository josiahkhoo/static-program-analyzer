//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_PARENT_T_ABSTRACTION_H
#define SPA_PARENT_T_ABSTRACTION_H


#include "common/entity/statement_entity.h"
#include "abstraction.h"

class ParentTAbstraction : public Abstraction<StatementEntity, StatementEntity> {
public:
    const StatementEntity &getLeftHandSide() override;

    const StatementEntity &getRightHandSide() override;
};


#endif //SPA_PARENT_T_ABSTRACTION_H
