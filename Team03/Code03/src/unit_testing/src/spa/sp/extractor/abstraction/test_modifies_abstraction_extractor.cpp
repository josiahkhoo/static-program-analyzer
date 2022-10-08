#include <algorithm>

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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE(modifies_s_abstractions.size() == 3);
    std::pair<int, std::string> p1 = {1, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));
    std::pair<int, std::string> p3 = {3, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p3) != modifies_s_vector.end()));

    REQUIRE(modifies_p_abstractions.size() == 3);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z2) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z3) != modifies_p_vector.end()));
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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE(modifies_s_abstractions.size() == 1);
    std::pair<int, std::string> p1 = {1, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));

    REQUIRE(modifies_p_abstractions.size() == 1);
    std::pair<std::string, std::string> z1 = {"p", "m"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE(modifies_s_abstractions.size() == 6);
    std::pair<int, std::string> p1 = {2, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {1, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));
    std::pair<int, std::string> p3 = {3, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p3) != modifies_s_vector.end()));
    std::pair<int, std::string> p4 = {1, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p5 = {4, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p5) != modifies_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p6) != modifies_s_vector.end()));

    REQUIRE(modifies_p_abstractions.size() == 3);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z2) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z3) != modifies_p_vector.end()));
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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE(modifies_s_abstractions.size() == 2);
    std::pair<int, std::string> p1 = {2, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {1, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));

    REQUIRE(modifies_p_abstractions.size() == 1);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE(modifies_s_abstractions.size() == 6);
    std::pair<int, std::string> p1 = {3, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p3) != modifies_s_vector.end()));
    std::pair<int, std::string> p4 = {5, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p5 = {4, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p5) != modifies_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p6) != modifies_s_vector.end()));

    REQUIRE(modifies_p_abstractions.size() == 2);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z2) != modifies_p_vector.end()));
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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        proc_node_call_ent_umap =
            AbstractionExtractorImpl::GetProcNodeCallEntityMap(
                eer.GetCallEntities());
    std::unordered_map<std::string, const TNode *> proc_name_node_umap =
        AbstractionExtractorImpl::GetProcNameNodeMap(
            eer.GetProcedureEntities());

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE(modifies_s_abstractions.size() == 6);
    std::pair<int, std::string> p1 = {3, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p3) != modifies_s_vector.end()));
    std::pair<int, std::string> p4 = {4, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p5 = {2, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p5) != modifies_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p6) != modifies_s_vector.end()));

    REQUIRE(modifies_p_abstractions.size() == 2);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z2) != modifies_p_vector.end()));
  }

  SECTION("Extract from chain call") {
    Lexer lexer;
    std::string input =
        "procedure p { call q; read x;} "
        "procedure q { call r; read y;} "
        "procedure r { read z;}";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(modifies_s_abstractions.empty());
    REQUIRE(modifies_s_abstractions.size() == 6);
    std::pair<int, std::string> p1 = {2, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {4, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));
    std::pair<int, std::string> p3 = {5, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p3) != modifies_s_vector.end()));
    std::pair<int, std::string> p4 = {3, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p5 = {1, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));

    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(modifies_p_abstractions.empty());
    REQUIRE(modifies_p_abstractions.size() == 6);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z2) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z3) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"q", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z4) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z5 = {"q", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z5) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z6 = {"r", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z6) != modifies_p_vector.end()));
  }

  SECTION("Extract from chain call") {
    Lexer lexer;
    std::string input =
        "procedure p { call q; call r; read x;} "
        "procedure q { call s; call s; read y;} "
        "procedure r { call q; read z;} "
        "procedure s { read m; } ";
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

    auto [modifies_s_abstractions, modifies_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> modifies_s_vector;
    for (auto i : modifies_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      modifies_s_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(modifies_s_abstractions.empty());
    REQUIRE(modifies_s_abstractions.size() == 13);
    std::pair<int, std::string> p1 = {1, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p1) != modifies_s_vector.end()));
    std::pair<int, std::string> p2 = {1, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p2) != modifies_s_vector.end()));
    std::pair<int, std::string> p3 = {2, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p3) != modifies_s_vector.end()));
    std::pair<int, std::string> p4 = {2, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p5 = {2, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p6 = {3, "x"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p4) != modifies_s_vector.end()));
    std::pair<int, std::string> p7 = {9, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p7) != modifies_s_vector.end()));
    std::pair<int, std::string> p8 = {4, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p8) != modifies_s_vector.end()));
    std::pair<int, std::string> p9 = {5, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p9) != modifies_s_vector.end()));
    std::pair<int, std::string> p10 = {6, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p10) != modifies_s_vector.end()));
    std::pair<int, std::string> p11 = {7, "y"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p11) != modifies_s_vector.end()));
    std::pair<int, std::string> p12 = {7, "m"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p12) != modifies_s_vector.end()));
    std::pair<int, std::string> p13 = {8, "z"};
    REQUIRE((std::find(modifies_s_vector.begin(), modifies_s_vector.end(),
                       p13) != modifies_s_vector.end()));

    std::vector<std::pair<std::string, std::string>> modifies_p_vector;
    for (auto i : modifies_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      modifies_p_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(modifies_p_abstractions.empty());
    REQUIRE(modifies_p_abstractions.size() == 10);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z1) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z2) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z3) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"p", "m"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z4) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z5 = {"s", "m"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z5) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z6 = {"q", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z6) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z7 = {"q", "m"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z7) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z8 = {"r", "m"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z8) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z9 = {"r", "z"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z9) != modifies_p_vector.end()));
    std::pair<std::string, std::string> z10 = {"r", "y"};
    REQUIRE((std::find(modifies_p_vector.begin(), modifies_p_vector.end(),
                       z10) != modifies_p_vector.end()));
  }
}