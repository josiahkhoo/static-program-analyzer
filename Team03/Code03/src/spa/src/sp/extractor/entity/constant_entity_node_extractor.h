//
// Created by Josiah Khoo on 26/8/22.
//

#ifndef SPA_CONSTANT_ENTITY_NODE_EXTRACTOR_H
#define SPA_CONSTANT_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/constant_entity.h"
#include "sp/extractor/node_extractor.h"

class ConstantEntityNodeExtractor : public NodeExtractor<ConstantEntity> {
 public:
  [[nodiscard]] std::optional<ConstantEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_CONSTANT_ENTITY_NODE_EXTRACTOR_H
