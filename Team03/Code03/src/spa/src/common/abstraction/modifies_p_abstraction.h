#ifndef SPA_MODIFIES_P_ABSTRACTION_H
#define SPA_MODIFIES_P_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/variable_entity.h"

class ModifiesPAbstraction
    : public Abstraction<ProcedureEntity, VariableEntity> {
 public:
  ModifiesPAbstraction(ProcedureEntity lhs, VariableEntity rhs);

  const ProcedureEntity &GetLeftHandSide() const override;

  const VariableEntity &GetRightHandSide() const override;

  bool operator==(const ModifiesPAbstraction &rhs) const;

  bool operator!=(const ModifiesPAbstraction &rhs) const;

 private:
  ProcedureEntity lhs_;
  VariableEntity rhs_;
};

#endif  // SPA_MODIFIES_P_ABSTRACTION_H
