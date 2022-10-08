#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_BI_SUB_ABSTRACTION_EXTRACTOR_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_BI_SUB_ABSTRACTION_EXTRACTOR_H_

#include "sub_abstraction_extractor_context.h"

template <class T, class U>
class BiSubAbstractionExtractor {
 public:
  virtual std::pair<std::vector<T>, std::vector<U>> Extract(
      const SubAbstractionExtractorContext& context) const = 0;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_BI_SUB_ABSTRACTION_EXTRACTOR_H_
