#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/abstraction/while_pattern_abstraction_extractor.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"

TEST_CASE("WhilePatternAbstraction Extractor",
          "[WhilePatternAbstractionExtractor]") {
  WhilePatternAbstractionExtractor extractor_under_test =
      WhilePatternAbstractionExtractor();
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

  SECTION("Extract from single Procedure with no while statements") {
    Lexer lexer;
    std::string input =
        "procedure p { if (x == 0) then { y = 2; } else { z = 1; } }";
    std::vector<Token> tokens = lexer.LexLine(input);
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
      "Extract from single Procedure with while statements not containing any "
      "variables") {
    Lexer lexer;
    std::string input = "procedure p { while (1 == 0) { y = 2; } }";
    std::vector<Token> tokens = lexer.LexLine(input);
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
      "Extract from single Procedure with while statements containing "
      "variables") {
    Lexer lexer;
    std::string input = "procedure p { while (x1 == y1) { h = 1; } }";
    std::vector<Token> tokens = lexer.LexLine(input);
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
