#ifndef SPA_ASSIGN_ENTITY_NODE_EXTRACTOR_H
#define SPA_ASSIGN_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/assign_entity.h"
#include "sp/extractor/node_extractor.h"

class AssignEntityNodeExtractor : public NodeExtractor<AssignEntity> {
 public:
  [[nodiscard]] std::optional<AssignEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_ASSIGN_ENTITY_NODE_EXTRACTOR_H
