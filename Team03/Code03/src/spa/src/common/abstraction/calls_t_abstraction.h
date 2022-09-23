#ifndef SPA_CALLS_T_ABSTRACTION_H
#define SPA_CALLS_T_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/procedure_entity.h"

class CallsTAbstraction : public Abstraction<ProcedureEntity, ProcedureEntity> {
 public:
  CallsTAbstraction(ProcedureEntity lhs, ProcedureEntity rhs);

  const ProcedureEntity &GetLeftHandSide() const override;

  const ProcedureEntity &GetRightHandSide() const override;

  bool operator==(const CallsTAbstraction &rhs) const;

  bool operator!=(const CallsTAbstraction &rhs) const;

 private:
  ProcedureEntity lhs_;
  ProcedureEntity rhs_;
};

#endif  // SPA_CALLS_T_ABSTRACTION_H
