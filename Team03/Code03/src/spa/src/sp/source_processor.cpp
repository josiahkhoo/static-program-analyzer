#include "source_processor.h"

#include "fstream"

SourceProcessor::SourceProcessor(Lexer &lexer,
                                 Parser<TNode, std::vector<Token>> &parser,
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
  storable_pkb.Store(design_extractor_result.GetAssignEntities());
  storable_pkb.Store(design_extractor_result.GetCallEntities());
  storable_pkb.Store(design_extractor_result.GetConstantEntities());
  storable_pkb.Store(design_extractor_result.GetIfEntities());
  storable_pkb.Store(design_extractor_result.GetPrintEntities());
  storable_pkb.Store(design_extractor_result.GetProcedureEntities());
  storable_pkb.Store(design_extractor_result.GetReadEntities());
  storable_pkb.Store(design_extractor_result.GetVariableEntities());
  storable_pkb.Store(design_extractor_result.GetWhileEntities());

  storable_pkb.Store(design_extractor_result.GetFollowsAbstractions());
  storable_pkb.Store(design_extractor_result.GetFollowsTAbstractions());
  storable_pkb.Store(design_extractor_result.GetParentAbstractions());
  storable_pkb.Store(design_extractor_result.GetParentTAbstractions());
  storable_pkb.Store(design_extractor_result.GetUsesSAbstractions());
  storable_pkb.Store(design_extractor_result.GetUsesPAbstractions());
  storable_pkb.Store(design_extractor_result.GetModifiesSAbstractions());
  storable_pkb.Store(design_extractor_result.GetModifiesPAbstractions());
  storable_pkb.Store(design_extractor_result.GetCallsAbstractions());
  storable_pkb.Store(design_extractor_result.GetCallsTAbstractions());
  storable_pkb.Store(design_extractor_result.GetIfPatternAbstractions());
  storable_pkb.Store(design_extractor_result.GetWhilePatternAbstractions());
  storable_pkb.Store(design_extractor_result.GetCFGExtractorResult());
}
