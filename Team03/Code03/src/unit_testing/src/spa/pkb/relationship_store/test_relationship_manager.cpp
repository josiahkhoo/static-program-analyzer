#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "catch.hpp"
#include "common/lexer.h"
#include "pkb/relationship_store/relationship_manager.h"
#include "sp/extractor/abstraction/modifies_abstraction_extractor_impl.h"
#include "sp/extractor/abstraction/uses_abstraction_extractor_impl.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/cfg_extractor_impl.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"

TEST_CASE("CFG_AFFECTS_QUERIES", "[CFGAffectsQueries]") {
  CFGExtractorImpl cfg_extractor_under_test = CFGExtractorImpl();
  SimpleParser parser;
  Lexer lexer;
  RelationshipManager relationship_manager;
  ModifiesAbstractionExtractorImpl modifies_extractor =
      ModifiesAbstractionExtractorImpl();
  UsesAbstractionExtractorImpl uses_extractor = UsesAbstractionExtractorImpl();

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

  std::string input =
      "procedure First "
      "{ "
      "x = 0;"
      "i = 5;"
      "while (i != 0) {"
      "x = x + 2 * y;"
      "call Second;"
      "i = i - 1;"
      "}"
      "if (x == 1) then {"
      "x = x + 1;"
      "} else {"
      "z = 1;"
      "}"
      "z = z + x + i;"
      "y = z + 2;"
      "x = x * y + z;"
      "}"
      "procedure Second "
      "{"
      "z = 5;"
      "v = z;"
      "print v;"
      "}";

  std::unordered_set<std::string> assigns(
      {"1", "2", "4", "6", "8", "9", "10", "11", "12", "13", "14"});
  std::unordered_set<std::string> calls({"5"});
  std::unordered_set<std::string> reads;

  std::vector<Token> tokens = lexer.LexLine(input);
  tokens.emplace_back(Token::END);
  auto ast = parser.Parse(tokens);
  std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
  for (auto cfg : res) {
    relationship_manager.AddCFG(cfg);
  }

  EntityExtractorResult eer = entity_extractor.Extract(ast);

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
      AbstractionExtractorImpl::GetProcNameNodeMap(eer.GetProcedureEntities());

  auto [modifies_s_abstractions, modifies_p_abstractions] =
      modifies_extractor.Extract(
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

  auto [uses_s_abstractions, uses_p_abstractions] = uses_extractor.Extract(
      {eer.GetAssignEntities(), eer.GetCallEntities(),
       eer.GetConstantEntities(), eer.GetIfEntities(), eer.GetPrintEntities(),
       eer.GetProcedureEntities(), eer.GetReadEntities(),
       eer.GetStatementEntities(), eer.GetVariableEntities(),
       eer.GetWhileEntities(), stmt_umap, var_umap, const_umap, proc_umap,
       proc_node_call_ent_umap, proc_name_node_umap});

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

  for (auto i : modifies_s_abstractions) {
    relationship_manager.AddAbstraction(i);
  }
  for (auto i : modifies_p_abstractions) {
    relationship_manager.AddAbstraction(i);
  }

  for (auto i : uses_s_abstractions) {
    relationship_manager.AddAbstraction(i);
  }
  for (auto i : uses_p_abstractions) {
    relationship_manager.AddAbstraction(i);
  }

  SECTION("Get Affects") {
    std::unordered_set<std::string> set_1({"1", "4", "8", "10", "11"});
    REQUIRE(relationship_manager.GetAffects(assigns, calls, reads, 12) ==
            set_1);
  }

  SECTION("Get Affects By") {
    std::unordered_set<std::string> set_1({"4", "8", "10", "12"});
    REQUIRE(relationship_manager.GetAffectsBy(assigns, calls, reads, 1) ==
            set_1);
  }

  SECTION("Get AffectsT") {
    std::unordered_set<std::string> set_1(
        {"1", "2", "4", "6", "8", "9", "10", "11"});
    REQUIRE(relationship_manager.GetAffectsT(assigns, calls, reads, 12) ==
            set_1);
  }

  SECTION("Get AffectsTBy") {
    std::unordered_set<std::string> set_1({"4", "8", "10", "11", "12"});
    REQUIRE(relationship_manager.GetAffectsTBy(assigns, calls, reads, 1) ==
            set_1);
  }
}
