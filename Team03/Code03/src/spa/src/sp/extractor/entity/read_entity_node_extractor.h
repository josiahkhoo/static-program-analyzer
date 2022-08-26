//
// Created by Josiah Khoo on 27/8/22.
//

#ifndef SPA_READ_ENTITY_NODE_EXTRACTOR_H
#define SPA_READ_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/read_entity.h"
#include "sp/extractor/node_extractor.h"

class ReadEntityNodeExtractor : public NodeExtractor<ReadEntity> {
 public:
  [[nodiscard]] std::optional<ReadEntity> TryExtractFromNode(const TNode& ast) const override;
};

#endif  // SPA_READ_ENTITY_NODE_EXTRACTOR_H
