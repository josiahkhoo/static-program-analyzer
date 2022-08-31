#include "catch.hpp"
#include "sp/extractor/abstraction/follows_abstraction_extractor.h"

TEST_CASE("FollowsAbstraction Extractor", "[FollowsAbstractionExtractor]") {
  FollowsAbstractionExtractor extractor_under_test =
      FollowsAbstractionExtractor();
  SECTION("Extract from Procedure") {
    TNode variable_node1 = TNode(TNode::Variable, 1, "x");
    TNode read_node1 =
        TNode(TNode::Read, 1, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(TNode::Variable, 2, "x");
    TNode read_node2 =
        TNode(TNode::Read, 2, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(TNode::Variable, 3, "x");
    TNode read_node3 =
        TNode(TNode::Read, 3, {std::make_shared<TNode>(variable_node3)});
    TNode procedure_node = TNode(TNode::Procedure, 0,
                                 {std::make_shared<TNode>(read_node1),
                                  std::make_shared<TNode>(read_node2),
                                  std::make_shared<TNode>(read_node3)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetLineNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetLineNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetLineNumber());
    ProcedureEntity p = ProcedureEntity(procedure_node, "proc");
    std::unordered_map<TNode, StatementEntity*> stmt_umap = {
        {*re1.GetNodePointer(), &re1},
        {*re2.GetNodePointer(), &re2},
        {*re3.GetNodePointer(), &re3},
    };
    std::unordered_map<TNode, VariableEntity*> var_umap = {
        {*v1.GetNodePointer(), &v1},
        {*v2.GetNodePointer(), &v2},
        {*v3.GetNodePointer(), &v3}};
    std::unordered_map<TNode, ConstantEntity*> const_umap = {};

    std::vector<FollowsAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {}, {}, {p}, {re1, re2, re3}, {re1, re2, re3}, {}, {},
        stmt_umap, var_umap, const_umap);

    REQUIRE(abstractions.size() == 2);
    // Check Follows(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide().GetNodePointer() ==
                 re1.GetNodePointer() &&
             abstractions[0].GetRightHandSide().GetNodePointer() ==
                 re2.GetNodePointer()));
    // Check Follows(2,3)
    REQUIRE((abstractions[1].GetLeftHandSide().GetNodePointer() ==
                 re2.GetNodePointer() &&
             abstractions[1].GetRightHandSide().GetNodePointer() ==
                 re3.GetNodePointer()));
  }

  SECTION("Extract from If") {
    TNode variable_node1 = TNode(TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(TNode::Read, 1, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(TNode::Read, 2, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(TNode::Read, 3, {std::make_shared<TNode>(variable_node3)});
    TNode if_node = TNode(TNode::Equal, 0, {});
    TNode then_node = TNode(TNode::StatementList, 0,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2),
                             std::make_shared<TNode>(read_node3)});
    TNode else_node = TNode(TNode::StatementList, 0, {});
    TNode if_else_then_node = TNode(
        TNode::IfElseThen, 0,
        {std::make_shared<TNode>(if_node), std::make_shared<TNode>(then_node),
         std::make_shared<TNode>(else_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetLineNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetLineNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetLineNumber());
    IfEntity if_ent = IfEntity(if_else_then_node, 1);
    std::unordered_map<TNode, StatementEntity*> stmt_umap = {
        {*re1.GetNodePointer(), &re1},
        {*re2.GetNodePointer(), &re2},
        {*re3.GetNodePointer(), &re3},
    };
    std::unordered_map<TNode, VariableEntity*> var_umap = {
        {*v1.GetNodePointer(), &v1},
        {*v2.GetNodePointer(), &v2},
        {*v3.GetNodePointer(), &v3}};
    std::unordered_map<TNode, ConstantEntity*> const_umap = {};

    std::vector<FollowsAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {if_ent}, {}, {}, {re1, re2, re3}, {re1, re2, re3}, {}, {},
        stmt_umap, var_umap, const_umap);

    REQUIRE(abstractions.size() == 2);
    // Check Follows(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide().GetNodePointer() ==
                 re1.GetNodePointer() &&
             abstractions[0].GetRightHandSide().GetNodePointer() ==
                 re2.GetNodePointer()));
    // Check Follows(2,3)
    REQUIRE((abstractions[1].GetLeftHandSide().GetNodePointer() ==
                 re2.GetNodePointer() &&
             abstractions[1].GetRightHandSide().GetNodePointer() ==
                 re3.GetNodePointer()));
  }

  SECTION("Extract from While") {
    TNode variable_node1 = TNode(TNode::Variable, 2, "x");
    TNode read_node1 =
        TNode(TNode::Read, 1, {std::make_shared<TNode>(variable_node1)});

    TNode variable_node2 = TNode(TNode::Variable, 3, "x");
    TNode read_node2 =
        TNode(TNode::Read, 2, {std::make_shared<TNode>(variable_node2)});

    TNode variable_node3 = TNode(TNode::Variable, 4, "x");
    TNode read_node3 =
        TNode(TNode::Read, 3, {std::make_shared<TNode>(variable_node3)});
    TNode cond_node = TNode(TNode::Equal, 0, {});
    TNode loop_node = TNode(TNode::StatementList, 0,
                            {std::make_shared<TNode>(read_node1),
                             std::make_shared<TNode>(read_node2),
                             std::make_shared<TNode>(read_node3)});
    TNode while_node = TNode(TNode::While, 0,
                             {std::make_shared<TNode>(cond_node),
                              std::make_shared<TNode>(loop_node)});

    VariableEntity v1 =
        VariableEntity(variable_node1, variable_node1.GetStringValue());
    VariableEntity v2 =
        VariableEntity(variable_node2, variable_node2.GetStringValue());
    VariableEntity v3 =
        VariableEntity(variable_node3, variable_node3.GetStringValue());
    ReadEntity re1 = ReadEntity(read_node1, read_node1.GetLineNumber());
    ReadEntity re2 = ReadEntity(read_node2, read_node2.GetLineNumber());
    ReadEntity re3 = ReadEntity(read_node3, read_node3.GetLineNumber());
    WhileEntity while_entity = WhileEntity(while_node, 1);
    std::unordered_map<TNode, StatementEntity*> stmt_umap = {
        {*re1.GetNodePointer(), &re1},
        {*re2.GetNodePointer(), &re2},
        {*re3.GetNodePointer(), &re3},
    };
    std::unordered_map<TNode, VariableEntity*> var_umap = {
        {*v1.GetNodePointer(), &v1},
        {*v2.GetNodePointer(), &v2},
        {*v3.GetNodePointer(), &v3}};
    std::unordered_map<TNode, ConstantEntity*> const_umap = {};

    std::vector<FollowsAbstraction> abstractions = extractor_under_test.Extract(
        {}, {}, {}, {}, {}, {}, {re1, re2, re3}, {re1, re2, re3}, {},
        {while_entity}, stmt_umap, var_umap, const_umap);

    REQUIRE(abstractions.size() == 2);
    // Check Follows(1,2)
    REQUIRE((abstractions[0].GetLeftHandSide().GetNodePointer() ==
                 re1.GetNodePointer() &&
             abstractions[0].GetRightHandSide().GetNodePointer() ==
                 re2.GetNodePointer()));
    // Check Follows(2,3)
    REQUIRE((abstractions[1].GetLeftHandSide().GetNodePointer() ==
                 re2.GetNodePointer() &&
             abstractions[1].GetRightHandSide().GetNodePointer() ==
                 re3.GetNodePointer()));
  }
}