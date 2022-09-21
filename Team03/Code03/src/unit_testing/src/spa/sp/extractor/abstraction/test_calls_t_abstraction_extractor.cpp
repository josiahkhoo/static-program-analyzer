#include <iostream>

#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/abstraction/calls_t_abstraction_extractor.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"

TEST_CASE("CallsTAbstraction Extractor", "[CallsTAbstractionExtractor]") {
  CallsTAbstractionExtractor extractor_under_test = CallsTAbstractionExtractor();
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

  SECTION("Extract from single Procedure with no call") {
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

    auto abstractions = extractor_under_test.Extract(
        eer.GetAssignEntities(), eer.GetCallEntities(),
        eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
        eer.GetProcedureEntities(), eer.GetReadEntities(),
        eer.GetStatementEntities(), eer.GetVariableEntities(),
        eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap);

    REQUIRE(abstractions.empty());
  }

  SECTION("Extract from Procedure with 2 call") {
    Lexer lexer;
    std::string input =
        "procedure main { m = x * y + z / 100; call second; call third;} "
        "procedure second { print x; } procedure third { print z; }";
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

    auto abstractions = extractor_under_test.Extract(
        eer.GetAssignEntities(), eer.GetCallEntities(),
        eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
        eer.GetProcedureEntities(), eer.GetReadEntities(),
        eer.GetStatementEntities(), eer.GetVariableEntities(),
        eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap);

    std::vector<std::pair<std::string, std::string>> calls_vector;
    for (auto i : abstractions) {
      std::string lhs_name = i.GetLeftHandSide().GetName();
      std::string rhs_name = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs_name, rhs_name};
      calls_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(abstractions.empty());
    REQUIRE(abstractions.size() == 2);
    std::pair<std::string, std::string> first = {"main", "second"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),first) != calls_vector.end()));
    std::pair<std::string, std::string> second = {"main", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),second) != calls_vector.end()));
  }

  SECTION("Extract from Procedure with chain call") {
    Lexer lexer;
    std::string input =
        "procedure main { m = x * y + z / 100; call second;} "
        "procedure second { call third; } procedure third { print z; }";
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

    auto abstractions = extractor_under_test.Extract(
        eer.GetAssignEntities(), eer.GetCallEntities(),
        eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
        eer.GetProcedureEntities(), eer.GetReadEntities(),
        eer.GetStatementEntities(), eer.GetVariableEntities(),
        eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap);

    std::vector<std::pair<std::string, std::string>> calls_vector;
    for (auto i : abstractions) {
      std::string lhs_name = i.GetLeftHandSide().GetName();
      std::string rhs_name = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs_name, rhs_name};
      calls_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(abstractions.empty());
    REQUIRE(abstractions.size() == 3);
    std::pair<std::string, std::string> first = {"main", "second"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),first) != calls_vector.end()));
    std::pair<std::string, std::string> second = {"main", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),second) != calls_vector.end()));
    std::pair<std::string, std::string> third = {"main", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),third) != calls_vector.end()));
  }

  SECTION("Extract from Procedure 2 calls and with chain call") {
    Lexer lexer;
    std::string input =
        "procedure main { m = x * y + z / 100; call second; call third;} "
        "procedure second { call third; } procedure third { print z; }";
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

    auto abstractions = extractor_under_test.Extract(
        eer.GetAssignEntities(), eer.GetCallEntities(),
        eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
        eer.GetProcedureEntities(), eer.GetReadEntities(),
        eer.GetStatementEntities(), eer.GetVariableEntities(),
        eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap);

    std::vector<std::pair<std::string, std::string>> calls_vector;
    for (auto i : abstractions) {
      std::string lhs_name = i.GetLeftHandSide().GetName();
      std::string rhs_name = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs_name, rhs_name};
      calls_vector.emplace_back(pair);
    }
    REQUIRE_FALSE(abstractions.empty());
    REQUIRE(abstractions.size() == 3);
    std::pair<std::string, std::string> first = {"main", "second"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),first) != calls_vector.end()));
    std::pair<std::string, std::string> second = {"main", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),second) != calls_vector.end()));
    std::pair<std::string, std::string> third = {"main", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),third) != calls_vector.end()));
  }

  SECTION("Extract from Procedure 2 calls and with chain call") {
    Lexer lexer;
    std::string input =
        "procedure main { m = x * y + z / 100; call second; call third;} "
        "procedure second { call third; } procedure third { call fourth; }"
        "procedure fourth { print z; }";
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

    auto abstractions = extractor_under_test.Extract(
        eer.GetAssignEntities(), eer.GetCallEntities(),
        eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
        eer.GetProcedureEntities(), eer.GetReadEntities(),
        eer.GetStatementEntities(), eer.GetVariableEntities(),
        eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap);

    std::vector<std::pair<std::string, std::string>> calls_vector;
    for (auto i : abstractions) {
      std::string lhs_name = i.GetLeftHandSide().GetName();
      std::string rhs_name = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs_name, rhs_name};
      calls_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(abstractions.empty());
    REQUIRE(abstractions.size() == 6);
    std::pair<std::string, std::string> first = {"main", "second"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),first) != calls_vector.end()));
    std::pair<std::string, std::string> second = {"main", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),second) != calls_vector.end()));
    std::pair<std::string, std::string> third = {"main", "fourth"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),third) != calls_vector.end()));
    std::pair<std::string, std::string> fourth = {"second", "third"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),fourth) != calls_vector.end()));
    std::pair<std::string, std::string> fifth = {"second", "fourth"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),fifth) != calls_vector.end()));
    std::pair<std::string, std::string> sixth = {"third", "fourth"};
    REQUIRE((std::find(calls_vector.begin(), calls_vector.end(),sixth) != calls_vector.end()));
  }
}

