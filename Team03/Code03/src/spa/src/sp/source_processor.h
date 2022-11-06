#ifndef SPA_SOURCE_PROCESSOR_H
#define SPA_SOURCE_PROCESSOR_H

#include <string>

#include "common/lexer.h"
#include "common/parser.h"
#include "common/t_node.h"
#include "pkb/impl/storable_pkb_impl.h"
#include "sp/extractor/design_extractor.h"

class SourceProcessor {
 public:
  SourceProcessor(Lexer &lexer, Parser<TNode, std::vector<Token>> &parser,
                  DesignExtractor &design_extractor, StorablePkbImpl &storable_pkb);

  void Process(const std::string &filename);

 private:
  Lexer &lexer_;
  Parser<TNode, std::vector<Token>> &parser_;
  DesignExtractor &design_extractor_;
  StorablePkbImpl &storable_pkb_;

  static void StoreDesignExtractorResult(
      const DesignExtractorResult &design_extractor_result,
      StorablePkbImpl &storable_pkb);
};

#endif  // SPA_SOURCE_PROCESSOR_H
