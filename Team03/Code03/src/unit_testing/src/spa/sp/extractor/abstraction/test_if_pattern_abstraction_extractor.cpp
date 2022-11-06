#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/abstraction/if_pattern_abstraction_extractor.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"

TEST_CASE("IfPatternAbstraction Extractor", "[IfPatternAbstractionExtractor]") {
  IfPatternAbstractionExtractor extractor_under_test =
      IfPatternAbstractionExtractor();
  SimpleParser parser;
  AssignEntityNodeExtractor assign_entity_node_extractor;
  CallEntityNodeExtractor call_entity_node_extractor;
  ConstantEntityNodeExtractor constant_entity_node_extractor;
  IfEntityNodeExtractor if_entity_node_extractor;
  PrintEntityNodeExtractor print_entity_node_extractor;
  ProcedureEntityNodeExtractor procedure_entity_node_extractor;
  ReadEntityNodeExtractor read_entity_node_extractor;
  StatementEntityNodeExtractor statement_entity_node_extractor;
  VariableEntityNodeExtractor variable_entity_node_extractor;
  WhileEntityNodeExtractor while_entity_node_extractor;
  EntityExtractorImpl entity_extractor = EntityExtractorImpl(
      assign_entity_node_extractor, call_entity_node_extractor,
      constant_entity_node_extractor, if_entity_node_extractor,
      print_entity_node_extractor, procedure_entity_node_extractor,
      read_entity_node_extractor, statement_entity_node_extractor,
      variable_entity_node_extractor, while_entity_node_extractor);
  std::vector<std::pair<Token::Kind, std::string>> tokenRules = {
      {Token::WHITESPACE, "^(\\s+)"},
      {Token::NUMBER, "^(\\d+)"},
      {Token::IDENTIFIER, "^[a-zA-Z]+[0-9]*"},
      {Token::LEFT_ROUND_BRACKET, "^(\\()"},
      {Token::RIGHT_ROUND_BRACKET, "^(\\))"},
      {Token::LEFT_CURLY_BRACKET, "^(\\{)"},
      {Token::RIGHT_CURLY_BRACKET, "^(\\})"},
      {Token::DOUBLE_EQUAL, "^(==)"},
      {Token::EQUAL, "^(=)"},
      {Token::LESS_THAN_OR_EQUAL, "^(<=)"},
      {Token::LESS_THAN, "^(<)"},
      {Token::GREATER_THAN_OR_EQUAL, "^(>=)"},
      {Token::GREATER_THAN, "^(>)"},
      {Token::PLUS, "^(\\+)"},
      {Token::MINUS, "^(\\-)"},
      {Token::ASTERISK, "^(\\*)"},
      {Token::SLASH, "^(\\/)"},
      {Token::COMMA, "^(,)"},
      {Token::PERIOD, "^(\\.)"},
      {Token::PERCENT, "^(%)"},
      {Token::SEMICOLON, "^(;)"},
      {Token::INVERTED_COMMAS, "^(\")"},
      {Token::UNDERSCORE, "^(_)"},
      {Token::HASHTAG, "^(#)"},
      {Token::OR, "^(\\|\\|)"},
      {Token::AND, "^(&&)"},
      {Token::NOT_EQUAL, "^(!=)"},
      {Token::NOT, "^(!)"},
      {Token::NEXT_LINE, "^(\n)"},
      {Token::END, "^(\0)"}};

  SECTION("Extract from single Procedure with no if statements") {
    Lexer lexer;
    std::string input = "procedure p { while(x == 0) { y = 2; } }";
    std::vector<Token> tokens = lexer.LexLine(input, tokenRules);
    tokens.emplace_back(Token::END);
    EntityExtractorResult eer = entity_extractor.Extract(parser.Parse(tokens));

    std::unordered_map<TNode, StatementEntity> stmt_umap =
        AbstractionExtractorImpl::GetTNodeStatementEntityMap(
            eer.GetStatementEntities());
    std::unordered_map<TNode, VariableEntity> var_umap =
        AbstractionExtractorImpl::GetTNodeVariableEntityMap(
            eer.GetVariableEntities());
    std::unordered_map<TNode, ConstantEntity> const_umap =
        AbstractionExtractorImpl::GetTNodeConstantEntityMap(
            eer.GetConstantEntities());
    std::unordered_map<TNode, ProcedureEntity> proc_umap =
        AbstractionExtractorImpl::GetTNodeProcedureEntityMap(
            eer.GetProcedureEntities());
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto abstractions = extractor_under_test.Extract(
        {eer.GetAssignEntities(), eer.GetCallEntities(),
         eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
         eer.GetProcedureEntities(), eer.GetReadEntities(),
         eer.GetStatementEntities(), eer.GetVariableEntities(),
         eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap,
         proc_node_call_ent_umap, proc_name_node_umap});

    REQUIRE(abstractions.empty());
  }

  SECTION(
      "Extract from single Procedure with if statements containing variables") {
    Lexer lexer;
    std::string input =
        "procedure p { if (1 == 0) then { y = 2; } else { z = 1; } }";
    std::vector<Token> tokens = lexer.LexLine(input, tokenRules);
    tokens.emplace_back(Token::END);
    EntityExtractorResult eer = entity_extractor.Extract(parser.Parse(tokens));

    std::unordered_map<TNode, StatementEntity> stmt_umap =
        AbstractionExtractorImpl::GetTNodeStatementEntityMap(
            eer.GetStatementEntities());
    std::unordered_map<TNode, VariableEntity> var_umap =
        AbstractionExtractorImpl::GetTNodeVariableEntityMap(
            eer.GetVariableEntities());
    std::unordered_map<TNode, ConstantEntity> const_umap =
        AbstractionExtractorImpl::GetTNodeConstantEntityMap(
            eer.GetConstantEntities());
    std::unordered_map<TNode, ProcedureEntity> proc_umap =
        AbstractionExtractorImpl::GetTNodeProcedureEntityMap(
            eer.GetProcedureEntities());
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto abstractions = extractor_under_test.Extract(
        {eer.GetAssignEntities(), eer.GetCallEntities(),
         eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
         eer.GetProcedureEntities(), eer.GetReadEntities(),
         eer.GetStatementEntities(), eer.GetVariableEntities(),
         eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap,
         proc_node_call_ent_umap, proc_name_node_umap});

    REQUIRE(abstractions.empty());
  }

  SECTION(
      "Extract from single Procedure with multi nested variable statements") {
    Lexer lexer;
    std::string input =
        "procedure p { if (!(x1 == y1)) then { a = 0; } else { b = 0; } }";
    std::vector<Token> tokens = lexer.LexLine(input, tokenRules);
    tokens.emplace_back(Token::END);
    EntityExtractorResult eer = entity_extractor.Extract(parser.Parse(tokens));

    std::unordered_map<TNode, StatementEntity> stmt_umap =
        AbstractionExtractorImpl::GetTNodeStatementEntityMap(
            eer.GetStatementEntities());
    std::unordered_map<TNode, VariableEntity> var_umap =
        AbstractionExtractorImpl::GetTNodeVariableEntityMap(
            eer.GetVariableEntities());
    std::unordered_map<TNode, ConstantEntity> const_umap =
        AbstractionExtractorImpl::GetTNodeConstantEntityMap(
            eer.GetConstantEntities());
    std::unordered_map<TNode, ProcedureEntity> proc_umap =
        AbstractionExtractorImpl::GetTNodeProcedureEntityMap(
            eer.GetProcedureEntities());
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto abstractions = extractor_under_test.Extract(
        {eer.GetAssignEntities(), eer.GetCallEntities(),
         eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
         eer.GetProcedureEntities(), eer.GetReadEntities(),
         eer.GetStatementEntities(), eer.GetVariableEntities(),
         eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap,
         proc_node_call_ent_umap, proc_name_node_umap});

    REQUIRE(abstractions.size() == 2);
    REQUIRE((abstractions[0].GetLeftHandSide().GetStatementNumber() == 1 &&
             abstractions[0].GetRightHandSide().GetName() == "x1"));
    REQUIRE((abstractions[1].GetLeftHandSide().GetStatementNumber() == 1 &&
             abstractions[1].GetRightHandSide().GetName() == "y1"));
  }
}
