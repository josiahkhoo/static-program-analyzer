#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/abstraction/modifies_abstraction_extractor_impl.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"

TEST_CASE("Modifies Abstraction Extractor Impl",
          "[ModifiesAbstractionExtractorImpl]") {
  ModifiesAbstractionExtractorImpl extractor_under_test =
      ModifiesAbstractionExtractorImpl();
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

  SECTION("Extract from Procedure with Read") {
    Lexer lexer;
    std::string input = "procedure p { read x; read y; read z; }";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            eer.GetAssignEntities(), eer.GetCallEntities(),
            eer.GetConstantEntities(), eer.GetIfEntities(),
            eer.GetPrintEntities(), eer.GetProcedureEntities(),
            eer.GetReadEntities(), eer.GetStatementEntities(),
            eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
            var_umap, const_umap, proc_umap);

    REQUIRE(modifies_s_abstractions.size() == 3);
    REQUIRE(
        (modifies_s_abstractions[0].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[0].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[1].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[1].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[2].GetLeftHandSide().GetStatementNumber() ==
             3 &&
         modifies_s_abstractions[2].GetRightHandSide().GetName() == "z"));

    REQUIRE(modifies_p_abstractions.size() == 3);
    REQUIRE((modifies_p_abstractions[0].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[0].GetRightHandSide().GetName() == "x"));
    REQUIRE((modifies_p_abstractions[1].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[1].GetRightHandSide().GetName() == "y"));
    REQUIRE((modifies_p_abstractions[2].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[2].GetRightHandSide().GetName() == "z"));
  }

  SECTION("Extract from Procedure with Assign") {
    Lexer lexer;
    std::string input = "procedure p { m = x * y + z / 100; }";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            eer.GetAssignEntities(), eer.GetCallEntities(),
            eer.GetConstantEntities(), eer.GetIfEntities(),
            eer.GetPrintEntities(), eer.GetProcedureEntities(),
            eer.GetReadEntities(), eer.GetStatementEntities(),
            eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
            var_umap, const_umap, proc_umap);

    REQUIRE(modifies_s_abstractions.size() == 1);
    REQUIRE(
        (modifies_s_abstractions[0].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[0].GetRightHandSide().GetName() == "m"));

    REQUIRE(modifies_p_abstractions.size() == 1);
    REQUIRE((modifies_p_abstractions[0].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[0].GetRightHandSide().GetName() == "m"));
  }

  SECTION("Extract from If") {
    Lexer lexer;
    std::string input =
        "procedure p { if (v == 0) then { read x; read y; } else { read z; "
        "} }";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            eer.GetAssignEntities(), eer.GetCallEntities(),
            eer.GetConstantEntities(), eer.GetIfEntities(),
            eer.GetPrintEntities(), eer.GetProcedureEntities(),
            eer.GetReadEntities(), eer.GetStatementEntities(),
            eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
            var_umap, const_umap, proc_umap);

    REQUIRE(modifies_s_abstractions.size() == 7);
    REQUIRE(
        (modifies_s_abstractions[0].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[0].GetRightHandSide().GetName() == "v"));
    REQUIRE(
        (modifies_s_abstractions[1].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[1].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[2].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[2].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[3].GetLeftHandSide().GetStatementNumber() ==
             3 &&
         modifies_s_abstractions[3].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[4].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[4].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[5].GetLeftHandSide().GetStatementNumber() ==
             4 &&
         modifies_s_abstractions[5].GetRightHandSide().GetName() == "z"));
    REQUIRE(
        (modifies_s_abstractions[6].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[6].GetRightHandSide().GetName() == "z"));

    REQUIRE(modifies_p_abstractions.size() == 4);
    REQUIRE((modifies_p_abstractions[0].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[0].GetRightHandSide().GetName() == "v"));
    REQUIRE((modifies_p_abstractions[1].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[1].GetRightHandSide().GetName() == "x"));
    REQUIRE((modifies_p_abstractions[2].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[2].GetRightHandSide().GetName() == "y"));
    REQUIRE((modifies_p_abstractions[3].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[3].GetRightHandSide().GetName() == "z"));
  }

  SECTION("Extract from While") {
    Lexer lexer;
    std::string input = "procedure p { while (v == 0) { read x; } }";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            eer.GetAssignEntities(), eer.GetCallEntities(),
            eer.GetConstantEntities(), eer.GetIfEntities(),
            eer.GetPrintEntities(), eer.GetProcedureEntities(),
            eer.GetReadEntities(), eer.GetStatementEntities(),
            eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
            var_umap, const_umap, proc_umap);

    REQUIRE(modifies_s_abstractions.size() == 3);
    REQUIRE(
        (modifies_s_abstractions[0].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[0].GetRightHandSide().GetName() == "v"));
    REQUIRE(
        (modifies_s_abstractions[1].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[1].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[2].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[2].GetRightHandSide().GetName() == "x"));

    REQUIRE(modifies_p_abstractions.size() == 2);
    REQUIRE((modifies_p_abstractions[0].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[0].GetRightHandSide().GetName() == "v"));
    REQUIRE((modifies_p_abstractions[1].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[1].GetRightHandSide().GetName() == "x"));
  }

  SECTION("Extract from nested If-While") {
    Lexer lexer;
    std::string input =
        "procedure p { if (m == 0) then { while (n == 0) { read x; } } else { "
        "while (o == 0) { read y; } } }";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            eer.GetAssignEntities(), eer.GetCallEntities(),
            eer.GetConstantEntities(), eer.GetIfEntities(),
            eer.GetPrintEntities(), eer.GetProcedureEntities(),
            eer.GetReadEntities(), eer.GetStatementEntities(),
            eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
            var_umap, const_umap, proc_umap);

    REQUIRE(modifies_s_abstractions.size() == 11);
    REQUIRE(
        (modifies_s_abstractions[0].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[0].GetRightHandSide().GetName() == "m"));
    REQUIRE(
        (modifies_s_abstractions[1].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[1].GetRightHandSide().GetName() == "n"));
    REQUIRE(
        (modifies_s_abstractions[2].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[2].GetRightHandSide().GetName() == "n"));
    REQUIRE(
        (modifies_s_abstractions[3].GetLeftHandSide().GetStatementNumber() ==
             3 &&
         modifies_s_abstractions[3].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[4].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[4].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[5].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[5].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[6].GetLeftHandSide().GetStatementNumber() ==
             4 &&
         modifies_s_abstractions[6].GetRightHandSide().GetName() == "o"));
    REQUIRE(
        (modifies_s_abstractions[7].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[7].GetRightHandSide().GetName() == "o"));
    REQUIRE(
        (modifies_s_abstractions[8].GetLeftHandSide().GetStatementNumber() ==
             5 &&
         modifies_s_abstractions[8].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[9].GetLeftHandSide().GetStatementNumber() ==
             4 &&
         modifies_s_abstractions[9].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[10].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[10].GetRightHandSide().GetName() == "y"));

    REQUIRE(modifies_p_abstractions.size() == 5);
    REQUIRE((modifies_p_abstractions[0].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[0].GetRightHandSide().GetName() == "m"));
    REQUIRE((modifies_p_abstractions[1].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[1].GetRightHandSide().GetName() == "n"));
    REQUIRE((modifies_p_abstractions[2].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[2].GetRightHandSide().GetName() == "x"));
    REQUIRE((modifies_p_abstractions[3].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[3].GetRightHandSide().GetName() == "o"));
    REQUIRE((modifies_p_abstractions[4].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[4].GetRightHandSide().GetName() == "y"));
  }

  SECTION("Extract from nested While-If") {
    Lexer lexer;
    std::string input =
        "procedure p { while (m == 0) { if (n == 0) then { read x; } else { "
        "read y; } } }";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            eer.GetAssignEntities(), eer.GetCallEntities(),
            eer.GetConstantEntities(), eer.GetIfEntities(),
            eer.GetPrintEntities(), eer.GetProcedureEntities(),
            eer.GetReadEntities(), eer.GetStatementEntities(),
            eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
            var_umap, const_umap, proc_umap);

    REQUIRE(modifies_s_abstractions.size() == 9);
    REQUIRE(
        (modifies_s_abstractions[0].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[0].GetRightHandSide().GetName() == "m"));
    REQUIRE(
        (modifies_s_abstractions[1].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[1].GetRightHandSide().GetName() == "n"));
    REQUIRE(
        (modifies_s_abstractions[2].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[2].GetRightHandSide().GetName() == "n"));
    REQUIRE(
        (modifies_s_abstractions[3].GetLeftHandSide().GetStatementNumber() ==
             3 &&
         modifies_s_abstractions[3].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[4].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[4].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[5].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[5].GetRightHandSide().GetName() == "x"));
    REQUIRE(
        (modifies_s_abstractions[6].GetLeftHandSide().GetStatementNumber() ==
             4 &&
         modifies_s_abstractions[6].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[7].GetLeftHandSide().GetStatementNumber() ==
             2 &&
         modifies_s_abstractions[7].GetRightHandSide().GetName() == "y"));
    REQUIRE(
        (modifies_s_abstractions[8].GetLeftHandSide().GetStatementNumber() ==
             1 &&
         modifies_s_abstractions[8].GetRightHandSide().GetName() == "y"));

    REQUIRE(modifies_p_abstractions.size() == 4);
    REQUIRE((modifies_p_abstractions[0].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[0].GetRightHandSide().GetName() == "m"));
    REQUIRE((modifies_p_abstractions[1].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[1].GetRightHandSide().GetName() == "n"));
    REQUIRE((modifies_p_abstractions[2].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[2].GetRightHandSide().GetName() == "x"));
    REQUIRE((modifies_p_abstractions[3].GetLeftHandSide().GetName() == "p" &&
             modifies_p_abstractions[3].GetRightHandSide().GetName() == "y"));
  }
};