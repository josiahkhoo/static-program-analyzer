//
// Created by Josiah Khoo on 27/8/22.
//

#ifndef SPA_PROCEDURE_ENTITY_NODE_EXTRACTOR_H
#define SPA_PROCEDURE_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/procedure_entity.h"
#include "sp/extractor/node_extractor.h"

class ProcedureEntityNodeExtractor : public NodeExtractor<ProcedureEntity> {
 public:
  [[nodiscard]] std::optional<ProcedureEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_PROCEDURE_ENTITY_NODE_EXTRACTOR_H
