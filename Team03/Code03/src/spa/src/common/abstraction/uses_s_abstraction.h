#ifndef SPA_USES_S_ABSTRACTION_H
#define SPA_USES_S_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"

class UsesSAbstraction : public Abstraction<StatementEntity, StatementEntity> {
public:
    UsesSAbstraction(StatementEntity lhs, StatementEntity rhs);

    const StatementEntity &GetLeftHandSide() const override;

    const StatementEntity &GetRightHandSide() const override;

    bool operator==(const UsesSAbstraction &rhs) const;

    bool operator!=(const UsesSAbstraction &rhs) const;

private:
    StatementEntity lhs_;
    StatementEntity rhs_;
};

#endif  // SPA_USES_S_ABSTRACTION_H
