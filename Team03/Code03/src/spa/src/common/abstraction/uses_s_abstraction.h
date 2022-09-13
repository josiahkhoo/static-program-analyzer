#ifndef SPA_USES_S_ABSTRACTION_H
#define SPA_USES_S_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"

class UsesSAbstraction : public Abstraction<StatementEntity, VariableEntity> {
 public:
  UsesSAbstraction(StatementEntity lhs, VariableEntity rhs);

  const StatementEntity &GetLeftHandSide() const override;

  const VariableEntity &GetRightHandSide() const override;

  bool operator==(const UsesSAbstraction &rhs) const;

  bool operator!=(const UsesSAbstraction &rhs) const;

 private:
  StatementEntity lhs_;
  VariableEntity rhs_;
};

#endif  // SPA_USES_S_ABSTRACTION_H
