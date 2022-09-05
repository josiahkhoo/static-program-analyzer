#ifndef SPA_PARENT_T_ABSTRACTION_H
#define SPA_PARENT_T_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"

class ParentTAbstraction
    : public Abstraction<StatementEntity, StatementEntity> {
 public:
  ParentTAbstraction(StatementEntity lhs, StatementEntity rhs);

  const StatementEntity &GetLeftHandSide() const override;

  const StatementEntity &GetRightHandSide() const override;

  bool operator==(const ParentTAbstraction &rhs) const;

  bool operator!=(const ParentTAbstraction &rhs) const;

 private:
  StatementEntity lhs_;
  StatementEntity rhs_;
};

#endif  // SPA_PARENT_T_ABSTRACTION_H
