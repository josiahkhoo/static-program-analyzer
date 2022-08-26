//
// Created by Josiah Khoo on 27/8/22.
//

#ifndef SPA_VARIABLE_ENTITY_NODE_EXTRACTOR_H
#define SPA_VARIABLE_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/variable_entity.h"
#include "sp/extractor/node_extractor.h"

class VariableEntityNodeExtractor : NodeExtractor<VariableEntity> {
 public:
  [[nodiscard]] std::optional<VariableEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_VARIABLE_ENTITY_NODE_EXTRACTOR_H
