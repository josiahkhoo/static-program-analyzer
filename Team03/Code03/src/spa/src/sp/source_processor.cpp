#include "source_processor.h"

#include "fstream"

SourceProcessor::SourceProcessor(Lexer &lexer, Parser<TNode> &parser,
                                 DesignExtractor &design_extractor,
                                 StorablePkb &storable_pkb)
    : lexer_(lexer),
      parser_(parser),
      design_extractor_(design_extractor),
      storable_pkb_(storable_pkb) {}

void SourceProcessor::Process(const std::string &filename) {
  std::ifstream source_file = std::ifstream(filename);
  if (!source_file) {
    throw std::runtime_error("Source file not found");
  }
  std::vector<Token> tokens = lexer_.Lex(source_file);
  TNode ast = parser_.Parse(tokens);
  DesignExtractorResult design_extractor_result =
      design_extractor_.Extract(ast);
  StoreDesignExtractorResult(design_extractor_result, storable_pkb_);
}

void SourceProcessor::StoreDesignExtractorResult(
    const DesignExtractorResult &design_extractor_result,
    StorablePkb &storable_pkb) {
  storable_pkb_.Store(
      design_extractor_result.GetEntityExtractorResult().GetAssignEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetCallEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetConstantEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetIfEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetPrintEntities());
  storable_pkb.Store(design_extractor_result.GetEntityExtractorResult()
                         .GetProcedureEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetReadEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetVariableEntities());
  storable_pkb.Store(
      design_extractor_result.GetEntityExtractorResult().GetWhileEntities());

  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetFollowsAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetFollowsTAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetParentAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetParentTAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetUsesSAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetUsesPAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetModifiesSAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetModifiesPAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetCallsAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetCallsTAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetIfPatternAbstractions());
  storable_pkb.Store(design_extractor_result.GetAbstractionExtractorResult()
                         .GetWhilePatternAbstractions());
}
