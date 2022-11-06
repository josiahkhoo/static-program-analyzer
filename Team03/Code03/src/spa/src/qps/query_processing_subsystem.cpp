#include "query_processing_subsystem.h"

#include "cached_queryable_pkb.h"
#include "common/exceptions/syntax_exception.h"
#include "qps/exceptions/semantic_exception.h"
#include "query_operation_checker.h"

QueryProcessingSubsystem::QueryProcessingSubsystem(
    const Lexer &lexer, Parser<QueryString, std::vector<Token>> &parser,
    const Planner &planner, const Evaluator &evaluator,
    QueryablePkb &queryable_pkb)
    : lexer_(lexer),
      parser_(parser),
      planner_(planner),
      evaluator_(evaluator),
      queryable_pkb_(queryable_pkb) {}

void QueryProcessingSubsystem::Process(std::string query,
                                       std::list<std::string> &results) {
  QueryString q_string;
  try {
    std::vector<Token> tokens = lexer_.LexLine(query);
    q_string = parser_.Parse(tokens);
  } catch (const SyntaxException &ex) {
    results.emplace_back(ex.what());
    return;  // Exit application
  } catch (const SemanticException &ex) {
    results.emplace_back(ex.what());
    return;
  }
  auto cached_queryable_pkb = CachedQueryablePkb(queryable_pkb_);
  QueryOperationChecker::Check(q_string, cached_queryable_pkb);
  std::shared_ptr<QNode> q_plan = planner_.Plan(q_string);
  std::unordered_set<std::string> q_res =
      evaluator_.Execute(cached_queryable_pkb, q_plan, q_string.GetSelect());
  results.insert(results.end(), q_res.begin(), q_res.end());
}
