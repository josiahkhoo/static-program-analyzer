#ifndef SPA_SUB_ABSTRACTION_EXTRACTOR_H
#define SPA_SUB_ABSTRACTION_EXTRACTOR_H

#include "sub_abstraction_extractor_context.h"

template <class T>
class SubAbstractionExtractor {
 public:
  virtual std::vector<T> Extract(
      const SubAbstractionExtractorContext& context) const = 0;
};

#endif  // SPA_SUB_ABSTRACTION_EXTRACTOR_H
