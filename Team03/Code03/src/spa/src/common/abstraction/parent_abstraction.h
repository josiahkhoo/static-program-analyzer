//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_PARENT_ABSTRACTION_H
#define SPA_PARENT_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"

class ParentAbstraction : public Abstraction<StatementEntity, StatementEntity> {
 public:
  ParentAbstraction(StatementEntity lhs, StatementEntity rhs);

  const StatementEntity &GetLeftHandSide() const override;

  const StatementEntity &GetRightHandSide() const override;

 private:
  StatementEntity lhs_;
  StatementEntity rhs_;
};

#endif  // SPA_PARENT_ABSTRACTION_H
