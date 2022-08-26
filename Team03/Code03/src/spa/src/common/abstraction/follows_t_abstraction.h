#ifndef SPA_FOLLOWS_T_ABSTRACTION_H
#define SPA_FOLLOWS_T_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"

class FollowsTAbstraction
    : public Abstraction<StatementEntity, StatementEntity> {
 public:
  FollowsTAbstraction(StatementEntity lhs, StatementEntity rhs);

  const StatementEntity &GetLeftHandSide() const override;

  const StatementEntity &GetRightHandSide() const override;

 private:
  StatementEntity lhs_;
  StatementEntity rhs_;
};

#endif  // SPA_FOLLOWS_T_ABSTRACTION_H
