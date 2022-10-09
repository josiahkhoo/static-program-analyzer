#ifndef SPA_CALLS_ABSTRACTION_EXTRACTOR_H
#define SPA_CALLS_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/calls_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class CallsAbstractionExtractor
    : public SubAbstractionExtractor<CallsAbstraction> {
 public:
  [[nodiscard]] std::vector<CallsAbstraction> Extract(
      const SubAbstractionExtractorContext& context) const override;
};
#endif  // SPA_CALLS_ABSTRACTION_EXTRACTOR_H
