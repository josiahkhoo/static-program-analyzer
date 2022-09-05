//
// Created by Josiah Khoo on 5/9/22.
//

#include "query_processing_subsystem.h"

#include <strstream>

QueryProcessingSubsystem::QueryProcessingSubsystem(
    const Lexer& lexer, QueryParser& query_parser, const Planner& planner,
    const Evaluator& evaluator, const QueryablePkb& queryable_pkb)
    : lexer_(lexer),
      query_parser_(query_parser),
      planner_(planner),
      evaluator_(evaluator),
      queryable_pkb_(queryable_pkb) {}

void QueryProcessingSubsystem::Process(std::string query,
                                       std::list<std::string>& results) {
  std::vector<Token> tokens = lexer_.LexLine(query);
  QueryString q_string = query_parser_.Parse(tokens);
  std::shared_ptr<QNode> q_plan = planner_.Plan(q_string);
  std::unordered_set<std::string> q_res =
      evaluator_.Execute(queryable_pkb_, q_plan);
  results.insert(results.end(), q_res.begin(), q_res.end());
}
