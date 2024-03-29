#ifndef SPA_PARENT_ABSTRACTION_H
#define SPA_PARENT_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"

class ParentAbstraction : public Abstraction<StatementEntity, StatementEntity> {
 public:
  ParentAbstraction(StatementEntity lhs, StatementEntity rhs);

  const StatementEntity &GetLeftHandSide() const override;

  const StatementEntity &GetRightHandSide() const override;

  bool operator==(const ParentAbstraction &rhs) const;

  bool operator!=(const ParentAbstraction &rhs) const;

 private:
  StatementEntity lhs_;
  StatementEntity rhs_;
};

#endif  // SPA_PARENT_ABSTRACTION_H
