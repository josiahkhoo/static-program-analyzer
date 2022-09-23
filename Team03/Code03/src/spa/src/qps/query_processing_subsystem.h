#ifndef SPA_QUERY_PROCESSING_SUBSYSTEM_H
#define SPA_QUERY_PROCESSING_SUBSYSTEM_H

#include <list>
#include <string>

#include "common/lexer.h"
#include "evaluator.h"
#include "planner.h"
#include "qps/parser/query_parser.h"

class QueryProcessingSubsystem {
 public:
  QueryProcessingSubsystem(const Lexer &lexer, const Planner &planner,
                           const Evaluator &evaluator,
                           const QueryablePkb &queryable_pkb);

  void Process(std::string query, std::list<std::string> &results);

 private:
  const Lexer &lexer_;
  const Planner &planner_;
  const Evaluator &evaluator_;
  const QueryablePkb &queryable_pkb_;
};

#endif  // SPA_QUERY_PROCESSING_SUBSYSTEM_H
