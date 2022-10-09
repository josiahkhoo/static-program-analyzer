#ifndef SPA_PARENT_ABSTRACTION_EXTRACTOR_H
#define SPA_PARENT_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/parent_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class ParentAbstractionExtractor
    : public SubAbstractionExtractor<ParentAbstraction> {
 public:
  std::vector<ParentAbstraction> Extract(
      const SubAbstractionExtractorContext& context) const override;
};

#endif  // SPA_PARENT_ABSTRACTION_EXTRACTOR_H
