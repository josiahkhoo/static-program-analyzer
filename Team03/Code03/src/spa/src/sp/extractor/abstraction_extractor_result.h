#ifndef SPA_ABSTRACTION_EXTRACTOR_RESULT_H
#define SPA_ABSTRACTION_EXTRACTOR_RESULT_H

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"

class AbstractionExtractorResult {
 public:
  AbstractionExtractorResult(
      std::vector<FollowsAbstraction> follows_abstractions,
      std::vector<FollowsTAbstraction> follows_t_abstractions,
      std::vector<ModifiesSAbstraction> modifies_s_abstractions,
      std::vector<ParentAbstraction> parent_abstractions,
      std::vector<ParentTAbstraction> parent_t_abstractions,
      std::vector<UsesSAbstraction> uses_s_abstractions);

  [[nodiscard]] std::vector<FollowsAbstraction> GetFollowsAbstractions() const;

  [[nodiscard]] std::vector<FollowsTAbstraction> GetFollowsTAbstractions()
      const;

  [[nodiscard]] std::vector<ModifiesSAbstraction> GetModifiesSAbstractions()
      const;

  [[nodiscard]] std::vector<ParentAbstraction> GetParentAbstractions() const;

  [[nodiscard]] std::vector<ParentTAbstraction> GetParentTAbstractions() const;

  [[nodiscard]] std::vector<UsesSAbstraction> GetUsesSAbstractions() const;

  bool operator==(const AbstractionExtractorResult &rhs) const;

  bool operator!=(const AbstractionExtractorResult &rhs) const;

 private:
  std::vector<FollowsAbstraction> follows_abstractions_;
  std::vector<FollowsTAbstraction> follows_t_abstractions_;
  std::vector<ModifiesSAbstraction> modifies_s_abstractions_;
  std::vector<ParentAbstraction> parent_abstractions_;
  std::vector<ParentTAbstraction> parent_t_abstractions_;
  std::vector<UsesSAbstraction> uses_s_abstractions_;
};

#endif  // SPA_ABSTRACTION_EXTRACTOR_RESULT_H
