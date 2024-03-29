#include "design_extractor_impl.h"

DesignExtractorImpl::DesignExtractorImpl(
    const EntityExtractor &entity_extractor, const CFGExtractor &cfg_extractor,
    const AbstractionExtractor &abstraction_extractor)
    : entity_extractor_(entity_extractor),
      cfg_extractor_(cfg_extractor),
      abstraction_extractor_(abstraction_extractor) {}

DesignExtractorResult DesignExtractorImpl::Extract(TNode ast) const {
  EntityExtractorResult eer = entity_extractor_.Extract(ast);

  std::vector<CFG> cfgs = cfg_extractor_.Extract(ast);

  AbstractionExtractorResult aer = abstraction_extractor_.Extract(
      eer.GetAssignEntities(), eer.GetCallEntities(), eer.GetConstantEntities(),
      eer.GetIfEntities(), eer.GetPrintEntities(), eer.GetProcedureEntities(),
      eer.GetReadEntities(), eer.GetStatementEntities(),
      eer.GetVariableEntities(), eer.GetWhileEntities());

  return {aer, cfgs, eer};
}
