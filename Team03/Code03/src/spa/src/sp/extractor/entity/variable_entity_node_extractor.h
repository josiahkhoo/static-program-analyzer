#ifndef SPA_VARIABLE_ENTITY_NODE_EXTRACTOR_H
#define SPA_VARIABLE_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/variable_entity.h"
#include "sp/extractor/node_extractor.h"

class VariableEntityNodeExtractor : public NodeExtractor<VariableEntity> {
 public:
  [[nodiscard]] std::optional<VariableEntity> TryExtractFromNode(
      const TNode &ast) const override;
};

#endif  // SPA_VARIABLE_ENTITY_NODE_EXTRACTOR_H
