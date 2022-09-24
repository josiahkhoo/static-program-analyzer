#ifndef SPA_QUERY_OPERATION_MATCHER_T_H
#define SPA_QUERY_OPERATION_MATCHER_T_H

#include <memory>

#include "qps/token_handler.h"

/// Utility class for matching T clause/operation starting grammar word(s)
class QueryOperationMatcherT {
 public:
  /// Checks if current tokens match clause/operation grammar word
  [[nodiscard]] static bool MatchParser(
      const std::shared_ptr<TokenHandler>& tokens, const std::string& word);
};
#endif  // SPA_QUERY_OPERATION_MATCHER_T_H
