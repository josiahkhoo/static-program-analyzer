//
// Created by Josiah Khoo on 13/9/22.
//

#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_ABSTRACTION_USES_P_ABSTRACTION_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_ABSTRACTION_USES_P_ABSTRACTION_H_

#include "abstraction.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/variable_entity.h"

class UsesPAbstraction : public Abstraction<ProcedureEntity, VariableEntity> {
 public:
  UsesPAbstraction(ProcedureEntity lhs, VariableEntity rhs);

  const ProcedureEntity &GetLeftHandSide() const override;

  const VariableEntity &GetRightHandSide() const override;

  bool operator==(const UsesPAbstraction &rhs) const;

  bool operator!=(const UsesPAbstraction &rhs) const;

 private:
  ProcedureEntity lhs_;
  VariableEntity rhs_;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_ABSTRACTION_USES_P_ABSTRACTION_H_
