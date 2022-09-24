#ifndef SPA_CALLS_ABSTRACTION_H
#define SPA_CALLS_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/procedure_entity.h"

class CallsAbstraction : public Abstraction<ProcedureEntity, ProcedureEntity> {
 public:
  CallsAbstraction(ProcedureEntity lhs, ProcedureEntity rhs);

  const ProcedureEntity &GetLeftHandSide() const override;

  const ProcedureEntity &GetRightHandSide() const override;

  bool operator==(const CallsAbstraction &rhs) const;

  bool operator!=(const CallsAbstraction &rhs) const;

 private:
  ProcedureEntity lhs_;
  ProcedureEntity rhs_;
};

#endif  // SPA_CALLS_ABSTRACTION_H
