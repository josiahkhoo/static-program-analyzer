#include "catch.hpp"
#include "sp/extractor/abstraction/parent_t_abstraction_extractor.h"

TEST_CASE("ParentTAbstraction Extractor", "[ParentTAbstractionExtractor]") {
  ParentTAbstractionExtractor extractor_under_test =
      ParentTAbstractionExtractor();
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

    std::vector<ParentTAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {}, {}, {p}, {re1, re2, re3}, {re1, re2, re3}, {}, {},
        stmt_umap, var_umap, const_umap);

    REQUIRE(abstractions.empty());
  }

  SECTION("Extract from nested If-If") {
    TNode variable_node1 = TNode(1, TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 2, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 3, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 4, {std::make_shared<TNode>(variable_node3)});

    // IF_ELSE_THEN NODE 2
    TNode variable_node4 = TNode(7, TNode::Variable, 6, "x");
    TNode read_node4 =
        TNode(8, TNode::Read, 6, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node5 = TNode(9, TNode::Variable, 7, "x");
    TNode read_node5 =
        TNode(10, TNode::Read, 7, {std::make_shared<TNode>(variable_node3)});
    TNode if_cond_node2 = TNode(11, TNode::Equal, 5, {});
    TNode then_node2 =
        TNode(12, TNode::StatementList, {std::make_shared<TNode>(read_node4)});
    TNode else_node2 =
        TNode(13, TNode::StatementList, {std::make_shared<TNode>(read_node5)});
    TNode if_else_then_node2 = TNode(14, TNode::IfElseThen, 5,
                                     {std::make_shared<TNode>(if_cond_node2),
                                      std::make_shared<TNode>(then_node2),
                                      std::make_shared<TNode>(else_node2)});

    // IF_ELSE_THEN NODE 1
    TNode if_cond_node = TNode(15, TNode::Equal, 1, {});
    TNode then_node = TNode(16, TNode::StatementList,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2)});
    TNode else_node = TNode(17, TNode::StatementList,
                            {std::make_shared<TNode>(read_node3),
                             std::make_shared<TNode>(if_else_then_node2)});
    TNode if_else_then_node = TNode(18, TNode::IfElseThen, 1,
                                    {std::make_shared<TNode>(if_cond_node),
                                     std::make_shared<TNode>(then_node),
                                     std::make_shared<TNode>(else_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    VariableEntity v4 =
        VariableEntity(variable_node4, variable_node4.GetStringValue());
    VariableEntity v5 =
        VariableEntity(variable_node5, variable_node5.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    ReadEntity re4 = ReadEntity(read_node4, read_node4.GetStatementNumber());
    ReadEntity re5 = ReadEntity(read_node5, read_node5.GetStatementNumber());
    IfEntity if_ent = IfEntity(if_else_then_node, 1);
    IfEntity if_ent2 = IfEntity(if_else_then_node2, 5);
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*if_ent2.GetNodePointer(), if_ent2},
        {*if_ent.GetNodePointer(), if_ent},
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
        {*re4.GetNodePointer(), re4},
        {*re5.GetNodePointer(), re5}};
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3},
        {*v4.GetNodePointer(), v4},
        {*v5.GetNodePointer(), v5}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};

    std::vector<ParentTAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {if_ent, if_ent2}, {}, {}, {re1, re2, re3, re4, re5},
        {re1, re2, re3, re4, re5}, {}, {}, stmt_umap, var_umap, const_umap);

    REQUIRE(abstractions.size() == 8);
    // Check Parent(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide() == if_ent &&
             abstractions[0].GetRightHandSide() == re1));
    // Check Parent(1,3)
    REQUIRE((abstractions[1].GetLeftHandSide() == if_ent &&
             abstractions[1].GetRightHandSide() == re2));
    // Check Parent(1,4)
    REQUIRE((abstractions[2].GetLeftHandSide() == if_ent &&
             abstractions[2].GetRightHandSide() == re3));
    // Check Parent(1,5)
    REQUIRE((abstractions[3].GetLeftHandSide() == if_ent &&
             abstractions[3].GetRightHandSide() == if_ent2));
    // Check Parent(1,6)
    REQUIRE((abstractions[4].GetLeftHandSide() == if_ent &&
             abstractions[4].GetRightHandSide() == re4));
    // Check Parent(1,7)
    REQUIRE((abstractions[5].GetLeftHandSide() == if_ent &&
             abstractions[5].GetRightHandSide() == re5));
    // Check Parent(5,6)
    REQUIRE((abstractions[6].GetLeftHandSide() == if_ent2 &&
             abstractions[6].GetRightHandSide() == re4));
    // Check Parent(5,7)
    REQUIRE((abstractions[7].GetLeftHandSide() == if_ent2 &&
             abstractions[7].GetRightHandSide() == re5));
  }

  SECTION("Extract from nested While-While") {
    TNode variable_node1 = TNode(1, TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 2, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 3, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 4, {std::make_shared<TNode>(variable_node3)});
    TNode cond_node = TNode(7, TNode::Equal, 1, {});

    // WHILE NODE 2
    TNode variable_node4 = TNode(8, TNode::Variable, 6, "x");
    TNode read_node4 =
        TNode(9, TNode::Read, 6, {std::make_shared<TNode>(variable_node3)});
    TNode cond_node2 = TNode(10, TNode::Equal, 5, {});
    TNode loop_node2 =
        TNode(11, TNode::StatementList, {std::make_shared<TNode>(read_node4)});
    TNode while_node2 = TNode(12, TNode::While, 5,
                              {std::make_shared<TNode>(cond_node2),
                               std::make_shared<TNode>(loop_node2)});

    // WHILE NODE 1
    TNode loop_node = TNode(13, TNode::StatementList,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2),
                             std::make_shared<TNode>(read_node3),
                             std::make_shared<TNode>(while_node2)});
    TNode while_node = TNode(14, TNode::While, 1,
                             {std::make_shared<TNode>(cond_node),
                              std::make_shared<TNode>(loop_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    VariableEntity v4 =
        VariableEntity(variable_node4, variable_node4.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    ReadEntity re4 = ReadEntity(read_node4, read_node4.GetStatementNumber());
    WhileEntity while_entity = WhileEntity(while_node, 1);
    WhileEntity while_entity2 = WhileEntity(while_node2, 5);
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*while_entity.GetNodePointer(), while_entity},
        {*while_entity2.GetNodePointer(), while_entity2},
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
        {*re4.GetNodePointer(), re4}};
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3},
        {*v4.GetNodePointer(), v4}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};

    std::vector<ParentTAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {}, {}, {}, {re1, re2, re3, re4}, {re1, re2, re3, re4}, {},
        {while_entity, while_entity2}, stmt_umap, var_umap, const_umap);

    REQUIRE(abstractions.size() == 6);
    // Check Parent(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide() == while_entity &&
             abstractions[0].GetRightHandSide() == re1));
    // Check Parent(1,3)
    REQUIRE((abstractions[1].GetLeftHandSide() == while_entity &&
             abstractions[1].GetRightHandSide() == re2));
    // Check Parent(1,4)
    REQUIRE((abstractions[2].GetLeftHandSide() == while_entity &&
             abstractions[2].GetRightHandSide() == re3));
    // Check Parent(1,5)
    REQUIRE((abstractions[3].GetLeftHandSide() == while_entity &&
             abstractions[3].GetRightHandSide() == while_entity2));
    // Check Parent(1,6)
    REQUIRE((abstractions[4].GetLeftHandSide() == while_entity &&
             abstractions[4].GetRightHandSide() == re4));
    // Check Parent(5,6)
    REQUIRE((abstractions[5].GetLeftHandSide() == while_entity2 &&
             abstractions[5].GetRightHandSide() == re4));
  }

  SECTION("Extract from nested While-If") {
    TNode variable_node1 = TNode(1, TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 2, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 3, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 4, {std::make_shared<TNode>(variable_node3)});
    TNode cond_node = TNode(7, TNode::Equal, 1, {});

    // IF NODE
    TNode variable_node4 = TNode(8, TNode::Variable, 6, "x");
    TNode read_node4 =
        TNode(9, TNode::Read, 6, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node5 = TNode(10, TNode::Variable, 7, "x");
    TNode read_node5 =
        TNode(11, TNode::Read, 7, {std::make_shared<TNode>(variable_node3)});
    TNode if_cond_node = TNode(12, TNode::Equal, 5, {});
    TNode then_node =
        TNode(13, TNode::StatementList, {std::make_shared<TNode>(read_node4)});
    TNode else_node =
        TNode(14, TNode::StatementList, {std::make_shared<TNode>(read_node5)});
    TNode if_else_then_node = TNode(15, TNode::IfElseThen, 5,
                                    {std::make_shared<TNode>(if_cond_node),
                                     std::make_shared<TNode>(then_node),
                                     std::make_shared<TNode>(else_node)});

    // WHILE NODE 1
    TNode loop_node = TNode(16, TNode::StatementList,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2),
                             std::make_shared<TNode>(read_node3),
                             std::make_shared<TNode>(if_else_then_node)});
    TNode while_node = TNode(17, TNode::While, 1,
                             {std::make_shared<TNode>(cond_node),
                              std::make_shared<TNode>(loop_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    VariableEntity v4 =
        VariableEntity(variable_node4, variable_node4.GetStringValue());
    VariableEntity v5 =
        VariableEntity(variable_node5, variable_node4.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    ReadEntity re4 = ReadEntity(read_node4, read_node4.GetStatementNumber());
    ReadEntity re5 = ReadEntity(read_node5, read_node5.GetStatementNumber());
    WhileEntity while_entity = WhileEntity(while_node, 1);
    IfEntity if_entity = IfEntity(if_else_then_node, 5);
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*while_entity.GetNodePointer(), while_entity},
        {*if_entity.GetNodePointer(), if_entity},
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
        {*re4.GetNodePointer(), re4},
        {*re5.GetNodePointer(), re5}};
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3},
        {*v4.GetNodePointer(), v4},
        {*v5.GetNodePointer(), v5}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};

    std::vector<ParentTAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {if_entity}, {}, {}, {re1, re2, re3, re4, re5},
        {re1, re2, re3, re4, re5}, {}, {while_entity}, stmt_umap, var_umap,
        const_umap);

    REQUIRE(abstractions.size() == 8);
    // Check Parent(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide() == while_entity &&
             abstractions[0].GetRightHandSide() == re1));
    // Check Parent(1,3)
    REQUIRE((abstractions[1].GetLeftHandSide() == while_entity &&
             abstractions[1].GetRightHandSide() == re2));
    // Check Parent(1,4)
    REQUIRE((abstractions[2].GetLeftHandSide() == while_entity &&
             abstractions[2].GetRightHandSide() == re3));
    // Check Parent(1,5)
    REQUIRE((abstractions[3].GetLeftHandSide() == while_entity &&
             abstractions[3].GetRightHandSide() == if_entity));
    // Check Parent(1,6)
    REQUIRE((abstractions[4].GetLeftHandSide() == while_entity &&
             abstractions[4].GetRightHandSide() == re4));
    // Check Parent(1,7)
    REQUIRE((abstractions[5].GetLeftHandSide() == while_entity &&
             abstractions[5].GetRightHandSide() == re5));
    // Check Parent(5,6)
    REQUIRE((abstractions[6].GetLeftHandSide() == if_entity &&
             abstractions[6].GetRightHandSide() == re4));
    // Check Parent(5,7)
    REQUIRE((abstractions[7].GetLeftHandSide() == if_entity &&
             abstractions[7].GetRightHandSide() == re5));
  }

  SECTION("Extract from nested If-While") {
    TNode variable_node1 = TNode(1, TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(2, TNode::Read, 2, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(3, TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(4, TNode::Read, 3, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(5, TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(6, TNode::Read, 4, {std::make_shared<TNode>(variable_node3)});

    // WHILE NODE
    TNode variable_node4 = TNode(7, TNode::Variable, 6, "x");
    TNode variable_node5 = TNode(8, TNode::Variable, 7, "x");
    TNode read_node4 =
        TNode(9, TNode::Read, 6, {std::make_shared<TNode>(variable_node4)});
    TNode read_node5 =
        TNode(10, TNode::Read, 7, {std::make_shared<TNode>(variable_node5)});
    TNode cond_node = TNode(11, TNode::Equal, 5, {});
    TNode loop_node = TNode(12, TNode::StatementList,
                            {std::make_shared<TNode>(read_node4),
                             std::make_shared<TNode>(read_node5)});
    TNode while_node = TNode(13, TNode::While, 5,
                             {std::make_shared<TNode>(cond_node),
                              std::make_shared<TNode>(loop_node)});

    // IF_ELSE_THEN NODE
    TNode if_cond_node = TNode(14, TNode::Equal, 1, {});
    TNode then_node = TNode(15, TNode::StatementList,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2)});
    TNode else_node = TNode(16, TNode::StatementList,
                            {std::make_shared<TNode>(read_node3),
                             std::make_shared<TNode>(while_node)});
    TNode if_else_then_node = TNode(17, TNode::IfElseThen, 1,
                                    {std::make_shared<TNode>(if_cond_node),
                                     std::make_shared<TNode>(then_node),
                                     std::make_shared<TNode>(else_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    VariableEntity v4 =
        VariableEntity(variable_node4, variable_node4.GetStringValue());
    VariableEntity v5 =
        VariableEntity(variable_node5, variable_node5.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetStatementNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetStatementNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetStatementNumber());
    ReadEntity re4 = ReadEntity(read_node4, read_node4.GetStatementNumber());
    ReadEntity re5 = ReadEntity(read_node5, read_node5.GetStatementNumber());
    IfEntity if_ent = IfEntity(if_else_then_node, 1);
    WhileEntity while_ent = WhileEntity(while_node, 5);
    std::unordered_map<TNode, StatementEntity> stmt_umap = {
        {*while_ent.GetNodePointer(), while_ent},
        {*if_ent.GetNodePointer(), if_ent},
        {*re1.GetNodePointer(), re1},
        {*re2.GetNodePointer(), re2},
        {*re3.GetNodePointer(), re3},
        {*re4.GetNodePointer(), re4},
        {*re5.GetNodePointer(), re5}};
    std::unordered_map<TNode, VariableEntity> var_umap = {
        {*v1.GetNodePointer(), v1},
        {*v2.GetNodePointer(), v2},
        {*v3.GetNodePointer(), v3},
        {*v4.GetNodePointer(), v4},
        {*v5.GetNodePointer(), v5}};
    std::unordered_map<TNode, ConstantEntity> const_umap = {};

    std::vector<ParentTAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {if_ent}, {}, {}, {re1, re2, re3, re4, re5},
        {re1, re2, re3, re4, re5}, {}, {while_ent}, stmt_umap, var_umap,
        const_umap);

    REQUIRE(abstractions.size() == 8);
    // Check Parent(5,6)
    REQUIRE((abstractions[0].GetLeftHandSide() == while_ent &&
             abstractions[0].GetRightHandSide() == re4));
    // Check Parent(5,7)
    REQUIRE((abstractions[1].GetLeftHandSide() == while_ent &&
             abstractions[1].GetRightHandSide() == re5));
    // Check Parent(1,2)
    REQUIRE((abstractions[2].GetLeftHandSide() == if_ent &&
             abstractions[2].GetRightHandSide() == re1));
    // Check Parent(1,3)
    REQUIRE((abstractions[3].GetLeftHandSide() == if_ent &&
             abstractions[3].GetRightHandSide() == re2));
    // Check Parent(1,4)
    REQUIRE((abstractions[4].GetLeftHandSide() == if_ent &&
             abstractions[4].GetRightHandSide() == re3));
    // Check Parent(1,5)
    REQUIRE((abstractions[5].GetLeftHandSide() == if_ent &&
             abstractions[5].GetRightHandSide() == while_ent));
    // Check Parent(1,6)
    REQUIRE((abstractions[6].GetLeftHandSide() == if_ent &&
             abstractions[6].GetRightHandSide() == re4));
    // Check Parent(1,7)
    REQUIRE((abstractions[7].GetLeftHandSide() == if_ent &&
             abstractions[7].GetRightHandSide() == re5));
  }
}