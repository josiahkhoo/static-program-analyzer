#ifndef SPA_DESIGN_EXTRACTOR_RESULT_H
#define SPA_DESIGN_EXTRACTOR_RESULT_H

#include "abstraction_extractor_result.h"
#include "entity_extractor_result.h"
#include "cfg.h"

class DesignExtractorResult {
 public:
  DesignExtractorResult(AbstractionExtractorResult abstraction_extractor_result,
                        std::vector<CFG> cfg_extractor_result,
                        EntityExtractorResult entity_extractor_result);

  [[nodiscard]] AbstractionExtractorResult GetAbstractionExtractorResult()
      const;

  [[nodiscard]] std::vector<CFG> GetCFGExtractorResult() const;

  [[nodiscard]] EntityExtractorResult GetEntityExtractorResult() const;

 private:
  AbstractionExtractorResult abstraction_extractor_result_;
  std::vector<CFG> cfg_extractor_result_;
  EntityExtractorResult entity_extractor_result_;
};

#endif  // SPA_DESIGN_EXTRACTOR_RESULT_H
