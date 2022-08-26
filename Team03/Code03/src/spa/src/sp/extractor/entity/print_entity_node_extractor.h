#ifndef SPA_PRINT_ENTITY_NODE_EXTRACTOR_H
#define SPA_PRINT_ENTITY_NODE_EXTRACTOR_H

#include "common/entity/print_entity.h"
#include "sp/extractor/node_extractor.h"

class PrintEntityNodeExtractor : public NodeExtractor<PrintEntity> {
 public:
  [[nodiscard]] std::optional<PrintEntity> TryExtractFromNode(
      const TNode& ast) const override;
};

#endif  // SPA_PRINT_ENTITY_NODE_EXTRACTOR_H
