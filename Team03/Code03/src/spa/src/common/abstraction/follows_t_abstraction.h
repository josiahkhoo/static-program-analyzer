//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_FOLLOWS_T_ABSTRACTION_H
#define SPA_FOLLOWS_T_ABSTRACTION_H


#include "common/entity/statement_entity.h"
#include "abstraction.h"

class FollowsTAbstraction : public Abstraction<StatementEntity, StatementEntity> {
public:
    const StatementEntity &getLeftHandSide() override;

    const StatementEntity &getRightHandSide() override;
};


#endif //SPA_FOLLOWS_T_ABSTRACTION_H
