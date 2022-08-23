//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_USES_S_ABSTRACTION_H
#define SPA_USES_S_ABSTRACTION_H


#include "common/entity/statement_entity.h"
#include "abstraction.h"

class UsesSAbstraction : public Abstraction<StatementEntity, StatementEntity> {
public:
    const StatementEntity &getLeftHandSide() override;

    const StatementEntity &getRightHandSide() override;
};


#endif //SPA_USES_S_ABSTRACTION_H
