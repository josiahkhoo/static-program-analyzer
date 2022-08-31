//
// Created by Josiah Khoo on 29/8/22.
//

#ifndef SPA_ABSTRACTION_EXTRACTOR_H
#define SPA_ABSTRACTION_EXTRACTOR_H

#include <unordered_map>

#include "abstraction_extractor_result.h"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"
#include "common/entity/while_entity.h"
#include "sp/extractor/abstraction/follows_abstraction_extractor.h"
#include "sp/extractor/abstraction/follows_t_abstraction_extractor.h"

class AbstractionExtractor {
 public:
  AbstractionExtractor(
      const FollowsAbstractionExtractor& follows_abstraction_extractor,
      const FollowsTAbstractionExtractor& follows_t_abstraction_extractor);
  [[nodiscard]] AbstractionExtractorResult Extract(
      const std::vector<AssignEntity>& assign_entities,
      const std::vector<CallEntity>& call_entities,
      const std::vector<ConstantEntity>& constant_entities,
      const std::vector<IfEntity>& if_entities,
      const std::vector<PrintEntity>& print_entities,
      const std::vector<ProcedureEntity>& procedure_entities,
      const std::vector<ReadEntity>& read_entities,
      const std::vector<StatementEntity>& statement_entities,
      const std::vector<VariableEntity>& variable_entities,
      const std::vector<WhileEntity>& while_entities) const;

 private:
  const FollowsAbstractionExtractor& follows_abstraction_extractor_;
  const FollowsTAbstractionExtractor& follows_t_abstraction_extractor_;

  [[nodiscard]] std::unordered_map<TNode, StatementEntity*>
  GetTNodeStatementEntityMap(
      const std::vector<StatementEntity>& statement_entities) const;

  [[nodiscard]] std::unordered_map<TNode, VariableEntity*>
  GetTNodeVariableEntityMap(
      const std::vector<VariableEntity>& variable_entities) const;

  [[nodiscard]] std::unordered_map<TNode, ConstantEntity*>
  GetTNodeConstantEntityMap(
      const std::vector<ConstantEntity>& constant_entities) const;
};

#endif  // SPA_ABSTRACTION_EXTRACTOR_H
