#ifndef SPA_MODIFIES_S_ABSTRACTION_H
#define SPA_MODIFIES_S_ABSTRACTION_H

#include "abstraction.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"

class ModifiesSAbstraction
        : public Abstraction<StatementEntity, VariableEntity> {
public:
    ModifiesSAbstraction(StatementEntity lhs, VariableEntity rhs);

    const StatementEntity &GetLeftHandSide() const override;

    const VariableEntity &GetRightHandSide() const override;

    bool operator==(const ModifiesSAbstraction &rhs) const;

    bool operator!=(const ModifiesSAbstraction &rhs) const;

private:
    StatementEntity lhs_;
    VariableEntity rhs_;
};

#endif  // SPA_MODIFIES_S_ABSTRACTION_H
