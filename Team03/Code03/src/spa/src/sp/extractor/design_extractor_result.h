#ifndef SPA_DESIGN_EXTRACTOR_RESULT_H
#define SPA_DESIGN_EXTRACTOR_RESULT_H

#include "abstraction_extractor_result.h"
#include "cfg.h"
#include "entity_extractor_result.h"

class DesignExtractorResult {
 public:
  DesignExtractorResult(AbstractionExtractorResult abstraction_extractor_result,
                        std::vector<CFG> cfg_extractor_result,
                        EntityExtractorResult entity_extractor_result);

  [[nodiscard]] std::vector<AssignEntity> GetAssignEntities() const;

  [[nodiscard]] std::vector<CallEntity> GetCallEntities() const;

  [[nodiscard]] std::vector<ConstantEntity> GetConstantEntities() const;

  [[nodiscard]] std::vector<IfEntity> GetIfEntities() const;

  [[nodiscard]] std::vector<PrintEntity> GetPrintEntities() const;

  [[nodiscard]] std::vector<ProcedureEntity> GetProcedureEntities() const;

  [[nodiscard]] std::vector<ReadEntity> GetReadEntities() const;

  [[nodiscard]] std::vector<StatementEntity> GetStatementEntities() const;

  [[nodiscard]] std::vector<VariableEntity> GetVariableEntities() const;

  [[nodiscard]] std::vector<WhileEntity> GetWhileEntities() const;

  [[nodiscard]] std::vector<FollowsAbstraction> GetFollowsAbstractions() const;

  [[nodiscard]] std::vector<FollowsTAbstraction> GetFollowsTAbstractions()
      const;

  [[nodiscard]] std::vector<ParentAbstraction> GetParentAbstractions() const;

  [[nodiscard]] std::vector<ParentTAbstraction> GetParentTAbstractions() const;

  [[nodiscard]] std::vector<CallsAbstraction> GetCallsAbstractions() const;

  [[nodiscard]] std::vector<CallsTAbstraction> GetCallsTAbstractions() const;

  [[nodiscard]] std::vector<UsesSAbstraction> GetUsesSAbstractions() const;

  [[nodiscard]] std::vector<UsesPAbstraction> GetUsesPAbstractions() const;

  [[nodiscard]] std::vector<ModifiesSAbstraction> GetModifiesSAbstractions()
      const;

  [[nodiscard]] std::vector<ModifiesPAbstraction> GetModifiesPAbstractions()
      const;

  [[nodiscard]] std::vector<IfPatternAbstraction> GetIfPatternAbstractions()
      const;

  [[nodiscard]] std::vector<WhilePatternAbstraction>
  GetWhilePatternAbstractions() const;

  [[nodiscard]] std::vector<CFG> GetCFGExtractorResult() const;

 private:
  AbstractionExtractorResult abstraction_extractor_result_;
  std::vector<CFG> cfg_extractor_result_;
  EntityExtractorResult entity_extractor_result_;
};

#endif  // SPA_DESIGN_EXTRACTOR_RESULT_H
