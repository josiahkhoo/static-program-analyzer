#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/abstraction/uses_abstraction_extractor_impl.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"

TEST_CASE("Uses Abstraction Extractor Impl", "[UsesAbstractionExtractorImpl]") {
  UsesAbstractionExtractorImpl extractor_under_test =
      UsesAbstractionExtractorImpl();
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

  SECTION("Extract from Procedure with Print") {
    Lexer lexer;
    std::string input = "procedure p { print x; print y; print z; }";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE(uses_s_abstractions.size() == 3);
    std::pair<int, std::string> p1 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {3, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));

    REQUIRE(uses_p_abstractions.size() == 3);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE(uses_s_abstractions.size() == 3);
    std::pair<int, std::string> p1 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));

    REQUIRE(uses_p_abstractions.size() == 3);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from If") {
    Lexer lexer;
    std::string input =
        "procedure p { if (v == 0) then { print x; print y; } else { print z; "
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE(uses_s_abstractions.size() == 7);
    std::pair<int, std::string> p1 = {1, "v"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p4 = {3, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p5 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p5) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p6 = {4, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p6) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p7 = {1, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p7) !=
             uses_s_vector.end()));

    REQUIRE(uses_p_abstractions.size() == 4);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"p", "v"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z4) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from While") {
    Lexer lexer;
    std::string input = "procedure p { while (v == 0) { print x; } }";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE(uses_s_abstractions.size() == 3);
    std::pair<int, std::string> p1 = {1, "v"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));

    REQUIRE(uses_p_abstractions.size() == 2);
    std::pair<std::string, std::string> z1 = {"p", "v"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from nested If-While") {
    Lexer lexer;
    std::string input =
        "procedure p { if (m == 0) then { while (n == 0) { print x; } } else { "
        "while (o == 0) { print y; } } }";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE(uses_s_abstractions.size() == 11);
    std::pair<int, std::string> p1 = {1, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "n"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "n"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p4 = {3, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p5 = {2, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p5) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p6) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p7 = {4, "o"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p7) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p8 = {1, "o"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p8) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p9 = {5, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p9) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p10 = {4, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p10) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p11 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p11) !=
             uses_s_vector.end()));

    REQUIRE(uses_p_abstractions.size() == 5);
    std::pair<std::string, std::string> z1 = {"p", "m"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "n"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"p", "o"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z4) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z5 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z5) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from nested While-If") {
    Lexer lexer;
    std::string input =
        "procedure p { while (m == 0) { if (n == 0) then { print x; } else { "
        "print y; } } }";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }
    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE(uses_s_abstractions.size() == 9);
    std::pair<int, std::string> p1 = {1, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {2, "n"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "n"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p4 = {3, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p5 = {2, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p5) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p6) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p7 = {4, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p7) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p8 = {2, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p8) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p9 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p9) !=
             uses_s_vector.end()));

    REQUIRE(uses_p_abstractions.size() == 4);
    std::pair<std::string, std::string> z1 = {"p", "m"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "n"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z4) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from chain call") {
    Lexer lexer;
    std::string input =
        "procedure p { call q; print x;} "
        "procedure q { call r; print y;} "
        "procedure r { print z;}";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(uses_s_abstractions.empty());
    REQUIRE(uses_s_abstractions.size() == 6);
    std::pair<int, std::string> p1 = {2, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {4, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {5, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p4 = {3, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p5 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p6 = {1, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));

    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(uses_p_abstractions.empty());
    REQUIRE(uses_p_abstractions.size() == 6);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"q", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z4) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z5 = {"q", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z5) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z6 = {"r", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z6) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from chain call") {
    Lexer lexer;
    std::string input =
        "procedure p { call q; call r; print x;} "
        "procedure q { call s; call s; print y;} "
        "procedure r { while (l == 0 ) { call q;} print z;} "
        "procedure s { print m; } ";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(uses_s_abstractions.empty());
    REQUIRE(uses_s_abstractions.size() == 15);
    std::pair<int, std::string> p1 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {1, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {2, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p4 = {2, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p5 = {2, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p6 = {3, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p7 = {10, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p7) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p8 = {4, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p8) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p9 = {5, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p9) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p10 = {6, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p10) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p11 = {8, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p11) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p12 = {8, "m"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p12) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p13 = {9, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p13) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p14 = {7, "l"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p14) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p15 = {2, "l"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p15) !=
             uses_s_vector.end()));

    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(uses_p_abstractions.empty());
    REQUIRE(uses_p_abstractions.size() == 12);
    std::pair<std::string, std::string> z1 = {"p", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"p", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"p", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"p", "m"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z4) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z5 = {"s", "m"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z5) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z6 = {"q", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z6) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z7 = {"q", "m"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z7) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z8 = {"r", "m"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z8) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z9 = {"r", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z9) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z10 = {"r", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z10) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z11 = {"r", "l"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z11) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z12 = {"p", "l"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z12) !=
             uses_p_vector.end()));
  }

  SECTION("Extract from multiple assign") {
    Lexer lexer;
    std::string input =
        "procedure Test {"
        "x = v + x * y + z * t;"
        "a = b;"
        "c = d * e * f * g;"
        "e = (100 + 2) * 6;"
        "}";
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

    auto [uses_s_abstractions, uses_p_abstractions] =
        extractor_under_test.Extract(
            {eer.GetAssignEntities(), eer.GetCallEntities(),
             eer.GetConstantEntities(), eer.GetIfEntities(),
             eer.GetPrintEntities(), eer.GetProcedureEntities(),
             eer.GetReadEntities(), eer.GetStatementEntities(),
             eer.GetVariableEntities(), eer.GetWhileEntities(), stmt_umap,
             var_umap, const_umap, proc_umap, proc_node_call_ent_umap,
             proc_name_node_umap});

    std::vector<std::pair<int, std::string>> uses_s_vector;
    for (auto i : uses_s_abstractions) {
      int lhs = i.GetLeftHandSide().GetStatementNumber();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<int, std::string> pair = {lhs, rhs};
      uses_s_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(uses_s_abstractions.empty());
    REQUIRE(uses_s_abstractions.size() == 10);
    std::pair<int, std::string> p1 = {1, "v"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p1) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p2 = {1, "x"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p2) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p3 = {1, "y"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p3) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p4 = {1, "z"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p5 = {1, "t"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p6 = {2, "b"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p4) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p7 = {3, "d"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p7) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p8 = {3, "e"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p8) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p9 = {3, "f"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p9) !=
             uses_s_vector.end()));
    std::pair<int, std::string> p10 = {3, "g"};
    REQUIRE((std::find(uses_s_vector.begin(), uses_s_vector.end(), p10) !=
             uses_s_vector.end()));

    std::vector<std::pair<std::string, std::string>> uses_p_vector;
    for (auto i : uses_p_abstractions) {
      std::string lhs = i.GetLeftHandSide().GetName();
      std::string rhs = i.GetRightHandSide().GetName();
      std::pair<std::string, std::string> pair = {lhs, rhs};
      uses_p_vector.emplace_back(pair);
    }

    REQUIRE_FALSE(uses_p_abstractions.empty());
    REQUIRE(uses_p_abstractions.size() == 10);
    std::pair<std::string, std::string> z1 = {"Test", "v"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z1) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z2 = {"Test", "x"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z2) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z3 = {"Test", "y"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z3) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z4 = {"Test", "z"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z4) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z5 = {"Test", "t"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z5) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z6 = {"Test", "b"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z6) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z7 = {"Test", "d"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z7) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z8 = {"Test", "e"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z8) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z9 = {"Test", "f"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z9) !=
             uses_p_vector.end()));
    std::pair<std::string, std::string> z10 = {"Test", "g"};
    REQUIRE((std::find(uses_p_vector.begin(), uses_p_vector.end(), z10) !=
             uses_p_vector.end()));
  }
};