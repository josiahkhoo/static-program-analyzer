//
// Created by Josiah Khoo on 27/8/22.
//

#ifndef SPA_WHILE_ENTITY_NODE_EXTRACTOR_H
#define SPA_WHILE_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/while_entity.h"
#include "sp/extractor/node_extractor.h"

class WhileEntityNodeExtractor : NodeExtractor<WhileEntity> {
 public:
  [[nodiscard]] std::optional<WhileEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_WHILE_ENTITY_NODE_EXTRACTOR_H
