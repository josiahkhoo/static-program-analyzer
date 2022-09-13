#ifndef SPA_ABSTRACTION_EXTRACTOR_IMPL_H
#define SPA_ABSTRACTION_EXTRACTOR_IMPL_H

#include <unordered_map>

#include "abstraction_extractor.h"
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
#include "sp/extractor/abstraction/parent_abstraction_extractor.h"
#include "sp/extractor/abstraction/parent_t_abstraction_extractor.h"

class AbstractionExtractorImpl : public AbstractionExtractor {
 public:
  AbstractionExtractorImpl(const SubAbstractionExtractor<FollowsAbstraction>
                               &follows_abstraction_extractor,
                           const SubAbstractionExtractor<FollowsTAbstraction>
                               &follows_t_abstraction_extractor,
                           const SubAbstractionExtractor<ParentAbstraction>
                               &parent_abstraction_extractor,
                           const SubAbstractionExtractor<ParentTAbstraction>
                               &parent_t_abstraction_extractor,
                           const SubAbstractionExtractor<UsesSAbstraction>
                               &uses_s_abstraction_extractor);

  [[nodiscard]] AbstractionExtractorResult Extract(
      const std::vector<AssignEntity> &assign_entities,
      const std::vector<CallEntity> &call_entities,
      const std::vector<ConstantEntity> &constant_entities,
      const std::vector<IfEntity> &if_entities,
      const std::vector<PrintEntity> &print_entities,
      const std::vector<ProcedureEntity> &procedure_entities,
      const std::vector<ReadEntity> &read_entities,
      const std::vector<StatementEntity> &statement_entities,
      const std::vector<VariableEntity> &variable_entities,
      const std::vector<WhileEntity> &while_entities) const override;

  [[nodiscard]] std::
      unordered_map<TNode, StatementEntity> static GetTNodeStatementEntityMap(
          const std::vector<StatementEntity> &statement_entities);

  [[nodiscard]] std::
      unordered_map<TNode, VariableEntity> static GetTNodeVariableEntityMap(
          const std::vector<VariableEntity> &variable_entities);

  [[nodiscard]] std::
      unordered_map<TNode, ConstantEntity> static GetTNodeConstantEntityMap(
          const std::vector<ConstantEntity> &constant_entities);

 private:
  const SubAbstractionExtractor<FollowsAbstraction>
      &follows_abstraction_extractor_;
  const SubAbstractionExtractor<FollowsTAbstraction>
      &follows_t_abstraction_extractor_;
  const SubAbstractionExtractor<ParentAbstraction>
      &parent_abstraction_extractor_;
  const SubAbstractionExtractor<ParentTAbstraction>
      &parent_t_abstraction_extractor_;
  const SubAbstractionExtractor<UsesSAbstraction>
      &uses_s_abstraction_extractor_;
};

#endif  // SPA_ABSTRACTION_EXTRACTOR_IMPL_H
