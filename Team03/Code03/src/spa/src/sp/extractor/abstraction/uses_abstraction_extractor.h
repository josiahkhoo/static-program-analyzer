#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_H_

#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"

class UsesAbstractionExtractor
    : public BiSubAbstractionExtractor<UsesSAbstraction, UsesPAbstraction> {
 public:
  [[nodiscard]] std::pair<std::vector<UsesSAbstraction>,
                          std::vector<UsesPAbstraction>>
  Extract(const SubAbstractionExtractorContext &context) const override = 0;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_H_
