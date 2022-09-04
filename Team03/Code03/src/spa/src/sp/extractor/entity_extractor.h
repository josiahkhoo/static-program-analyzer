#ifndef SPA_ENTITY_EXTRACTOR_H
#define SPA_ENTITY_EXTRACTOR_H

#include "common/t_node.h"
#include "entity_extractor_result.h"

class EntityExtractor {
 public:
  virtual EntityExtractorResult Extract(const TNode &ast) const = 0;
};

#endif  // SPA_ENTITY_EXTRACTOR_H
