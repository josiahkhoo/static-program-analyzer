#include "query_processing_subsystem.h"

#include "qps/exceptions/semantic_exception.h"
#include "qps/exceptions/syntax_exception.h"

QueryProcessingSubsystem::QueryProcessingSubsystem(
    const Lexer &lexer, Parser<QueryString, std::vector<Token>> &parser,
    const Planner &planner, const Evaluator &evaluator,
    const QueryablePkb &queryable_pkb)
    : lexer_(lexer),
      parser_(parser),
      planner_(planner),
      evaluator_(evaluator),
      queryable_pkb_(queryable_pkb) {}

void QueryProcessingSubsystem::Process(std::string query,
                                       std::list<std::string> &results) {
  std::vector<Token> tokens = lexer_.LexLine(query, true);
  QueryString q_string;
  try {
    q_string = parser_.Parse(tokens);
  } catch (const SyntaxException &ex) {
    results.emplace_back(ex.what());
    return;  // Exit application
  } catch (const SemanticException &ex) {
    results.emplace_back(ex.what());
    return;
  }
  std::shared_ptr<QNode> q_plan = planner_.Plan(q_string);
  std::unordered_set<std::string> q_res =
      evaluator_.Execute(queryable_pkb_, q_plan, q_string.GetSelect());
  results.insert(results.end(), q_res.begin(), q_res.end());
}
