//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_MODIFIES_S_ABSTRACTION_H
#define SPA_MODIFIES_S_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"

class ModifiesSAbstraction : public Abstraction<StatementEntity, Entity> {
 public:
  ModifiesSAbstraction(StatementEntity lhs, Entity rhs);

  const StatementEntity &GetLeftHandSide() const override;

  const Entity &GetRightHandSide() const override;

 private:
  StatementEntity lhs_;
  Entity rhs_;
};

#endif  // SPA_MODIFIES_S_ABSTRACTION_H
