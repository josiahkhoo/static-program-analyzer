#ifndef SPA_ASSIGN_ENTITY_EXTRACTOR_H
#define SPA_ASSIGN_ENTITY_EXTRACTOR_H

#include "common/entity/assign_entity.h"
#include "sp/extractor/extractor.h"

class EntityExtractor : public Extractor<AssignEntity> {
  std::vector<AssignEntity> extract(const TNode& ast) override;
};

#endif  // SPA_ASSIGN_ENTITY_EXTRACTOR_H
