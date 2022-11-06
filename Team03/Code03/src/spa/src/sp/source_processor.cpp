#include "source_processor.h"

#include "fstream"

SourceProcessor::SourceProcessor(Lexer &lexer,
                                 Parser<TNode, std::vector<Token>> &parser,
                                 DesignExtractor &design_extractor,
                                 StorablePkbImpl &storable_pkb)
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
    StorablePkbImpl &storable_pkb) {
  storable_pkb.GetEntityStorablePkb().GetAssignEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetAssignEntities());
  storable_pkb.GetEntityStorablePkb().GetCallEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetCallEntities());
  storable_pkb.GetEntityStorablePkb().GetConstantEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetConstantEntities());
  storable_pkb.GetEntityStorablePkb().GetIfEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetIfEntities());
  storable_pkb.GetEntityStorablePkb().GetPrintEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetPrintEntities());
  storable_pkb.GetEntityStorablePkb().GetProcedureEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult()
          .GetProcedureEntities());
  storable_pkb.GetEntityStorablePkb().GetReadEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetReadEntities());
  storable_pkb.GetEntityStorablePkb().GetVariableEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetVariableEntities());
  storable_pkb.GetEntityStorablePkb().GetWhileEntityStorable().Store(
      design_extractor_result.GetEntityExtractorResult().GetWhileEntities());

  storable_pkb.GetAbstractionStorablePkb().GetFollowsStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetFollowsAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetFollowsTStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetFollowsTAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetParentStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetParentAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetParentTStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetParentTAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetUsesSStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetUsesSAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetUsesPStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetUsesPAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetModifiesSStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetModifiesSAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetModifiesPStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetModifiesPAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetCallsStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetCallsAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetCallsTStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetCallsTAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetIfPatternStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetIfPatternAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetWhilePatternStorable().Store(
      design_extractor_result.GetAbstractionExtractorResult()
          .GetWhilePatternAbstractions());
  storable_pkb.GetAbstractionStorablePkb().GetCfgStorable().Store(
      design_extractor_result.GetCFGExtractorResult());
}
