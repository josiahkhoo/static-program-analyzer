#ifndef SPA_DESIGN_EXTRACTOR_H
#define SPA_DESIGN_EXTRACTOR_H

#include <unordered_map>

#include "abstraction_extractor.h"
#include "design_extractor_result.h"
#include "entity_extractor.h"

class DesignExtractor {
 public:
  DesignExtractor(const EntityExtractor &entity_extractor,
                  const AbstractionExtractor &abstraction_extractor);
  DesignExtractorResult Extract(TNode ast);

 public:
 private:
  const EntityExtractor &entity_extractor_;
  const AbstractionExtractor &abstraction_extractor_;
};

#endif  // SPA_DESIGN_EXTRACTOR_H
