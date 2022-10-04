#ifndef SPA_SYNONYM_SELECT_PARSER_H
#define SPA_SYNONYM_SELECT_PARSER_H

#include "qps/parser/query_select_parser.h"

/// Parser tokens and creates a new SynonymSelect object
class SynonymSelectParser : public QuerySelectParser {
 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<Select> Parse(TokenBuilderPair data) override;
};

#endif  // SPA_SYNONYM_SELECT_PARSER_H
