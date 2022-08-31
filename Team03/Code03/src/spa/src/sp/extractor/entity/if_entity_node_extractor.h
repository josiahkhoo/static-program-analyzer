#ifndef SPA_IF_ENTITY_NODE_EXTRACTOR_H
#define SPA_IF_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/if_entity.h"
#include "sp/extractor/node_extractor.h"

class IfEntityNodeExtractor : public NodeExtractor<IfEntity> {
 public:
  [[nodiscard]] std::optional<IfEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_IF_ENTITY_NODE_EXTRACTOR_H
