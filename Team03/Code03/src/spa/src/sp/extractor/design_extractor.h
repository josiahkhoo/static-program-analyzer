#ifndef SPA_DESIGN_EXTRACTOR_H
#define SPA_DESIGN_EXTRACTOR_H

#include <unordered_map>

#include "abstraction_extractor.h"
#include "design_extractor_result.h"
#include "entity_extractor.h"

class DesignExtractor {
 public:
  DesignExtractor(const EntityExtractor &entity_extractor,
                  const AbstractionExtractor &abstraction_extractor);
  DesignExtractorResult Extract(TNode ast);

 public:
 private:
  const EntityExtractor &entity_extractor_;
  const AbstractionExtractor &abstraction_extractor_;

  [[nodiscard]] std::unordered_map<TNode, StatementEntity>
  GetTNodeStatementEntityMap(
      const std::vector<StatementEntity> &statement_entities) const;

  [[nodiscard]] std::unordered_map<TNode, VariableEntity>
  GetTNodeVariableEntityMap(
      const std::vector<VariableEntity> &variable_entities) const;

  [[nodiscard]] std::unordered_map<TNode, ConstantEntity>
  GetTNodeConstantEntityMap(
      const std::vector<ConstantEntity> &constant_entities) const;
};

#endif  // SPA_DESIGN_EXTRACTOR_H
