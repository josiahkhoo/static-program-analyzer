//
// Created by Josiah Khoo on 27/8/22.
//

#ifndef SPA_STATEMENT_ENTITY_NODE_EXTRACTOR_H
#define SPA_STATEMENT_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/statement_entity.h"
#include "sp/extractor/node_extractor.h"

class StatementEntityNodeExtractor : NodeExtractor<StatementEntity> {
 public:
  StatementEntityNodeExtractor() {}

  [[nodiscard]] std::optional<StatementEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_STATEMENT_ENTITY_NODE_EXTRACTOR_H
