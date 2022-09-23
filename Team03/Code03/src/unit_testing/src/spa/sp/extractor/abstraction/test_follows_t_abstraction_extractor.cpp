#include "catch.hpp"
#include "sp/extractor/abstraction/follows_t_abstraction_extractor.h"

TEST_CASE("FollowsTAbstraction Extractor", "[FollowsAbstractionExtractor]") {
  FollowsTAbstractionExtractor extractor_under_test =
      FollowsTAbstractionExtractor();
  SECTION("Extract from Procedure") {
    TNode variable_node1 = TNode(1, TNode::Variable, 1, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 1, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 2, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 2, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 3, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 3, {std::make_shared<TNode>(variable_node3)});
    TNode statement_list_node = TNode(7, TNode::StatementList,
                                      {std::make_shared<TNode>(read_node1),
                                       std::make_shared<TNode>(read_node2),
                                       std::make_shared<TNode>(read_node3)});
    TNode procedure_node = TNode(
        8, TNode::Procedure, {std::make_shared<TNode>(statement_list_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    ProcedureEntity p = ProcedureEntity(procedure_node, "proc");
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
    };
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};
    std::unordered_map<TNode, ProcedureEntity> proc_umap = {};
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>> proc_node_call_ent_umap = {};
    std::unordered_map<std::string, const TNode *> proc_name_node_umap = {};


    std::vector<FollowsTAbstraction> abstractions =
        extractor_under_test.Extract({}, {}, {}, {}, {}, {p}, {re1, re2, re3},
                                     {re1, re2, re3}, {}, {}, stmt_umap,
                                     var_umap, const_umap, proc_umap, proc_node_call_ent_umap, proc_name_node_umap);

    REQUIRE(abstractions.size() == 3);
    // Check Follows(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide() == re1 &&
             abstractions[0].GetRightHandSide() == re2));
    // Check Follows(1,3)
    REQUIRE((abstractions[1].GetLeftHandSide() == re1 &&
             abstractions[1].GetRightHandSide() == re3));
    // Check Follows(2,3)
    REQUIRE((abstractions[2].GetLeftHandSide() == re2 &&
             abstractions[2].GetRightHandSide() == re3));
  }

  SECTION("Extract from If") {
    TNode variable_node1 = TNode(1, TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 1, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 2, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 3, {std::make_shared<TNode>(variable_node3)});
    TNode if_node = TNode(7, TNode::Equal, 0, {});
    TNode then_node = TNode(8, TNode::StatementList, 0,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2),
                             std::make_shared<TNode>(read_node3)});
    TNode else_node = TNode(9, TNode::StatementList, 0, {});
    TNode if_else_then_node = TNode(
        10, TNode::IfElseThen, 0,
        {std::make_shared<TNode>(if_node), std::make_shared<TNode>(then_node),
         std::make_shared<TNode>(else_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    IfEntity if_ent = IfEntity(if_else_then_node, 1);
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
    };
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};
    std::unordered_map<TNode, ProcedureEntity> proc_umap = {};
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>> proc_node_call_ent_umap = {};
    std::unordered_map<std::string, const TNode *> proc_name_node_umap = {};

    std::vector<FollowsTAbstraction> abstractions =
        extractor_under_test.Extract(
            {}, {}, {}, {if_ent}, {}, {}, {re1, re2, re3}, {re1, re2, re3}, {},
            {}, stmt_umap, var_umap, const_umap, proc_umap, proc_node_call_ent_umap, proc_name_node_umap);

    REQUIRE(abstractions.size() == 3);
    // Check Follows(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide() == re1 &&
             abstractions[0].GetRightHandSide() == re2));
    // Check Follows(1,3)
    REQUIRE((abstractions[1].GetLeftHandSide() == re1 &&
             abstractions[1].GetRightHandSide() == re3));
    // Check Follows(2,3)
    REQUIRE((abstractions[2].GetLeftHandSide() == re2 &&
             abstractions[2].GetRightHandSide() == re3));
  }

  SECTION("Extract from While") {
    TNode variable_node1 = TNode(1, TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 1, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 2, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 3, {std::make_shared<TNode>(variable_node3)});
    TNode cond_node = TNode(7, TNode::Equal, 0, {});
    TNode loop_node = TNode(8, TNode::StatementList, 0,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2),
                             std::make_shared<TNode>(read_node3)});
    TNode while_node = TNode(9, TNode::While, 0,
                             {std::make_shared<TNode>(cond_node),
                              std::make_shared<TNode>(loop_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    WhileEntity while_entity = WhileEntity(while_node, 1);
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
    };
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};
    std::unordered_map<TNode, ProcedureEntity> proc_umap = {};
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>> proc_node_call_ent_umap = {};
    std::unordered_map<std::string, const TNode *> proc_name_node_umap = {};

    std::vector<FollowsTAbstraction> abstractions =
        extractor_under_test.Extract(
            {}, {}, {}, {}, {}, {}, {re1, re2, re3}, {re1, re2, re3}, {},
            {while_entity}, stmt_umap, var_umap, const_umap, proc_umap, proc_node_call_ent_umap, proc_name_node_umap);

    REQUIRE(abstractions.size() == 3);
    // Check Follows(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide() == re1 &&
             abstractions[0].GetRightHandSide() == re2));
    // Check Follows(1,3)
    REQUIRE((abstractions[1].GetLeftHandSide() == re1 &&
             abstractions[1].GetRightHandSide() == re3));
    // Check Follows(2,3)
    REQUIRE((abstractions[2].GetLeftHandSide() == re2 &&
             abstractions[2].GetRightHandSide() == re3));
  }
}