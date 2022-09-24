#ifndef SPA_WHILE_PATTERN_ABSTRACTION_H_
#define SPA_WHILE_PATTERN_ABSTRACTION_H_

#include "abstraction.h"
#include "common/entity/variable_entity.h"
#include "common/entity/while_entity.h"

/// The WhilePatternAbstraction refers to the conditional expression within a
/// while statement using a variable.
class WhilePatternAbstraction
    : public Abstraction<WhileEntity, VariableEntity> {
 public:
  WhilePatternAbstraction(WhileEntity lhs, VariableEntity rhs);

  [[nodiscard]] const WhileEntity &GetLeftHandSide() const override;

  [[nodiscard]] const VariableEntity &GetRightHandSide() const override;
  bool operator==(const WhilePatternAbstraction &rhs) const;
  bool operator!=(const WhilePatternAbstraction &rhs) const;

 private:
  WhileEntity lhs_;
  VariableEntity rhs_;
};

#endif  // SPA_WHILE_PATTERN_ABSTRACTION_H_
