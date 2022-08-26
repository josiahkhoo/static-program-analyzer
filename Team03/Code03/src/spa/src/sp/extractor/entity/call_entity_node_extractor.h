//
// Created by Josiah Khoo on 26/8/22.
//

#ifndef SPA_CALL_ENTITY_NODE_EXTRACTOR_H
#define SPA_CALL_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/call_entity.h"
#include "sp/extractor/node_extractor.h"

class CallEntityNodeExtractor : public NodeExtractor<CallEntity> {
 public:
  [[nodiscard]] std::optional<CallEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_CALL_ENTITY_NODE_EXTRACTOR_H
