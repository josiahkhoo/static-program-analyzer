#ifndef SPA_IF_PATTERN_ABSTRACTION_H_
#define SPA_IF_PATTERN_ABSTRACTION_H_

#include "abstraction.h"
#include "common/entity/if_entity.h"
#include "common/entity/variable_entity.h"

/// The IfPatternAbstraction refers to the conditional expression within a
/// if statement using a variable.
class IfPatternAbstraction : public Abstraction<IfEntity, VariableEntity> {
 public:
  IfPatternAbstraction(IfEntity lhs, VariableEntity rhs);

  [[nodiscard]] const IfEntity &GetLeftHandSide() const override;

  [[nodiscard]] const VariableEntity &GetRightHandSide() const override;
  bool operator==(const IfPatternAbstraction &rhs) const;
  bool operator!=(const IfPatternAbstraction &rhs) const;

 private:
  IfEntity lhs_;
  VariableEntity rhs_;
};

#endif  // SPA_IF_PATTERN_ABSTRACTION_H_
