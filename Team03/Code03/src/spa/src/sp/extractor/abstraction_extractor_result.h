#ifndef SPA_ABSTRACTION_EXTRACTOR_RESULT_H
#define SPA_ABSTRACTION_EXTRACTOR_RESULT_H

#include "common/abstraction/calls_abstraction.h"
#include "common/abstraction/calls_t_abstraction.h"
#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/abstraction/if_pattern_abstraction.h"
#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"
#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "common/abstraction/while_pattern_abstraction.h"

class AbstractionExtractorResult {
 public:
  AbstractionExtractorResult(
      std::vector<FollowsAbstraction> follows_abstractions,
      std::vector<FollowsTAbstraction> follows_t_abstractions,
      std::vector<ParentAbstraction> parent_abstractions,
      std::vector<ParentTAbstraction> parent_t_abstractions,
      std::vector<CallsAbstraction> calls_abstractions,
      std::vector<CallsTAbstraction> calls_t_abstractions,
      std::vector<UsesSAbstraction> uses_s_abstractions,
      std::vector<UsesPAbstraction> uses_p_abstractions,
      std::vector<ModifiesSAbstraction> modifies_s_abstractions,
      std::vector<ModifiesPAbstraction> modifies_p_abstractions,
      std::vector<IfPatternAbstraction> if_pattern_abstractions,
      std::vector<WhilePatternAbstraction> while_pattern_abstractions);

  [[nodiscard]] std::vector<FollowsAbstraction> GetFollowsAbstractions() const;

  [[nodiscard]] std::vector<FollowsTAbstraction> GetFollowsTAbstractions()
      const;

  [[nodiscard]] std::vector<ParentAbstraction> GetParentAbstractions() const;

  [[nodiscard]] std::vector<ParentTAbstraction> GetParentTAbstractions() const;

  [[nodiscard]] std::vector<CallsAbstraction> GetCallsAbstractions() const;

  [[nodiscard]] std::vector<CallsTAbstraction> GetCallsTAbstractions() const;

  [[nodiscard]] std::vector<UsesSAbstraction> GetUsesSAbstractions() const;

  [[nodiscard]] std::vector<UsesPAbstraction> GetUsesPAbstractions() const;

  [[nodiscard]] std::vector<ModifiesSAbstraction> GetModifiesSAbstractions()
      const;

  [[nodiscard]] std::vector<ModifiesPAbstraction> GetModifiesPAbstractions()
      const;

  [[nodiscard]] std::vector<IfPatternAbstraction> GetIfPatternAbstractions()
      const;

  [[nodiscard]] std::vector<WhilePatternAbstraction>
  GetWhilePatternAbstractions() const;

  bool operator==(const AbstractionExtractorResult &rhs) const;

  bool operator!=(const AbstractionExtractorResult &rhs) const;

  class Builder {
   public:
    Builder();
    Builder FollowsAbstractions(
        std::vector<FollowsAbstraction> *follows_abstractions);
    Builder FollowsTAbstractions(
        std::vector<FollowsTAbstraction> *follows_t_abstractions);
    Builder ParentAbstractions(
        std::vector<ParentAbstraction> *parent_abstractions);
    Builder ParentTAbstractions(
        std::vector<ParentTAbstraction> *parent_t_abstractions);
    Builder CallsAbstractions(
        std::vector<CallsAbstraction> *calls_abstractions);
    Builder CallsTAbstractions(
        std::vector<CallsTAbstraction> *calls_t_abstractions);
    Builder UsesSAbstractions(
        std::vector<UsesSAbstraction> *uses_s_abstractions);
    Builder UsesPAbstractions(
        std::vector<UsesPAbstraction> *uses_p_abstractions);
    Builder ModifiesSAbstractions(
        std::vector<ModifiesSAbstraction> *modifies_s_abstractions);
    Builder ModifiesPAbstractions(
        std::vector<ModifiesPAbstraction> *modifies_p_abstractions);
    Builder IfPatternAbstractions(
        std::vector<IfPatternAbstraction> *if_pattern_abstractions);
    Builder WhilePatternAbstractions(
        std::vector<WhilePatternAbstraction> *while_pattern_abstractions);
    AbstractionExtractorResult Build();

   private:
    std::vector<FollowsAbstraction> *follows_abstractions_;
    std::vector<FollowsTAbstraction> *follows_t_abstractions_;
    std::vector<ParentAbstraction> *parent_abstractions_;
    std::vector<ParentTAbstraction> *parent_t_abstractions_;
    std::vector<CallsAbstraction> *calls_abstractions_;
    std::vector<CallsTAbstraction> *calls_t_abstractions_;
    std::vector<UsesSAbstraction> *uses_s_abstractions_;
    std::vector<UsesPAbstraction> *uses_p_abstractions_;
    std::vector<ModifiesSAbstraction> *modifies_s_abstractions_;
    std::vector<ModifiesPAbstraction> *modifies_p_abstractions_;
    std::vector<IfPatternAbstraction> *if_pattern_abstractions_;
    std::vector<WhilePatternAbstraction> *while_pattern_abstractions_;
  };

 private:
  std::vector<FollowsAbstraction> follows_abstractions_;
  std::vector<FollowsTAbstraction> follows_t_abstractions_;
  std::vector<ParentAbstraction> parent_abstractions_;
  std::vector<ParentTAbstraction> parent_t_abstractions_;
  std::vector<CallsAbstraction> calls_abstractions_;
  std::vector<CallsTAbstraction> calls_t_abstractions_;
  std::vector<UsesSAbstraction> uses_s_abstractions_;
  std::vector<UsesPAbstraction> uses_p_abstractions_;
  std::vector<ModifiesSAbstraction> modifies_s_abstractions_;
  std::vector<ModifiesPAbstraction> modifies_p_abstractions_;
  std::vector<IfPatternAbstraction> if_pattern_abstractions_;
  std::vector<WhilePatternAbstraction> while_pattern_abstractions_;
};

#endif  // SPA_ABSTRACTION_EXTRACTOR_RESULT_H
