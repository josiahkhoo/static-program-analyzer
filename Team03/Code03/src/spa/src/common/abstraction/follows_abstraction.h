//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_FOLLOWS_ABSTRACTION_H
#define SPA_FOLLOWS_ABSTRACTION_H


#include "abstraction.h"
#include "common/entity/statement_entity.h"

class FollowsAbstraction : public Abstraction<StatementEntity, StatementEntity> {
public:
    const StatementEntity &getLeftHandSide() override;

    const StatementEntity &getRightHandSide() override;
};


#endif //SPA_FOLLOWS_ABSTRACTION_H
