#include "design_extractor_result.h"

#include <utility>

DesignExtractorResult::DesignExtractorResult(
    AbstractionExtractorResult abstraction_extractor_result,
    std::vector<CFG> cfg_extractor_result,
    EntityExtractorResult entity_extractor_result)
    : abstraction_extractor_result_(std::move(abstraction_extractor_result)),
      cfg_extractor_result_(std::move(cfg_extractor_result)),
      entity_extractor_result_(std::move(entity_extractor_result)) {}

std::vector<CFG> DesignExtractorResult::GetCFGExtractorResult() const {
  return cfg_extractor_result_;
}

std::vector<AssignEntity> DesignExtractorResult::GetAssignEntities() const {
  return entity_extractor_result_.GetAssignEntities();
}

std::vector<CallEntity> DesignExtractorResult::GetCallEntities() const {
  return entity_extractor_result_.GetCallEntities();
}

std::vector<ConstantEntity> DesignExtractorResult::GetConstantEntities() const {
  return entity_extractor_result_.GetConstantEntities();
}

std::vector<IfEntity> DesignExtractorResult::GetIfEntities() const {
  return entity_extractor_result_.GetIfEntities();
}

std::vector<PrintEntity> DesignExtractorResult::GetPrintEntities() const {
  return entity_extractor_result_.GetPrintEntities();
}

std::vector<ProcedureEntity> DesignExtractorResult::GetProcedureEntities()
    const {
  return entity_extractor_result_.GetProcedureEntities();
}

std::vector<ReadEntity> DesignExtractorResult::GetReadEntities() const {
  return entity_extractor_result_.GetReadEntities();
}

std::vector<StatementEntity> DesignExtractorResult::GetStatementEntities()
    const {
  return entity_extractor_result_.GetStatementEntities();
}

std::vector<VariableEntity> DesignExtractorResult::GetVariableEntities() const {
  return entity_extractor_result_.GetVariableEntities();
}

std::vector<WhileEntity> DesignExtractorResult::GetWhileEntities() const {
  return entity_extractor_result_.GetWhileEntities();
}

std::vector<FollowsAbstraction> DesignExtractorResult::GetFollowsAbstractions()
    const {
  return abstraction_extractor_result_.GetFollowsAbstractions();
}

std::vector<FollowsTAbstraction>
DesignExtractorResult::GetFollowsTAbstractions() const {
  return abstraction_extractor_result_.GetFollowsTAbstractions();
}

std::vector<ParentAbstraction> DesignExtractorResult::GetParentAbstractions()
    const {
  return abstraction_extractor_result_.GetParentAbstractions();
}

std::vector<ParentTAbstraction> DesignExtractorResult::GetParentTAbstractions()
    const {
  return abstraction_extractor_result_.GetParentTAbstractions();
}

std::vector<CallsAbstraction> DesignExtractorResult::GetCallsAbstractions()
    const {
  return abstraction_extractor_result_.GetCallsAbstractions();
}

std::vector<CallsTAbstraction> DesignExtractorResult::GetCallsTAbstractions()
    const {
  return abstraction_extractor_result_.GetCallsTAbstractions();
}

std::vector<UsesSAbstraction> DesignExtractorResult::GetUsesSAbstractions()
    const {
  return abstraction_extractor_result_.GetUsesSAbstractions();
}

std::vector<UsesPAbstraction> DesignExtractorResult::GetUsesPAbstractions()
    const {
  return abstraction_extractor_result_.GetUsesPAbstractions();
}

std::vector<ModifiesSAbstraction>
DesignExtractorResult::GetModifiesSAbstractions() const {
  return abstraction_extractor_result_.GetModifiesSAbstractions();
}

std::vector<ModifiesPAbstraction>
DesignExtractorResult::GetModifiesPAbstractions() const {
  return abstraction_extractor_result_.GetModifiesPAbstractions();
}

std::vector<IfPatternAbstraction>
DesignExtractorResult::GetIfPatternAbstractions() const {
  return abstraction_extractor_result_.GetIfPatternAbstractions();
}

std::vector<WhilePatternAbstraction>
DesignExtractorResult::GetWhilePatternAbstractions() const {
  return abstraction_extractor_result_.GetWhilePatternAbstractions();
}