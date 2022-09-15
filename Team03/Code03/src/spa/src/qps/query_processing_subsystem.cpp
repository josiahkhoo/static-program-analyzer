#include "query_processing_subsystem.h"

QueryProcessingSubsystem::QueryProcessingSubsystem(
    const Lexer &lexer, const Planner &planner, const Evaluator &evaluator,
    const QueryablePkb &queryable_pkb)
    : lexer_(lexer),
      planner_(planner),
      evaluator_(evaluator),
      queryable_pkb_(queryable_pkb) {}

void QueryProcessingSubsystem::Process(std::string query,
                                       std::list<std::string> &results) {
  try {
    std::vector<Token> tokens = lexer_.LexLine(query);
    QueryParser parser;
    QueryString q_string = parser.Parse(tokens);
    std::shared_ptr<QNode> q_plan = planner_.Plan(q_string);
    std::unordered_set<std::string> q_res =
        evaluator_.Execute(queryable_pkb_, q_plan);
    results.insert(results.end(), q_res.begin(), q_res.end());
  } catch (const std::exception& ex) {
    results.emplace_back(ex.what());
  }
}
