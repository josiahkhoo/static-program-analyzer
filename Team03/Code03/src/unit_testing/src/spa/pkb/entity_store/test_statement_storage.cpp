#include "catch.hpp"
#include "pkb/entity_store/statement_storage.h"

TEST_CASE("Call Storage Management", "[StatementStorage]") {
  TNode mock_call_node =
      TNode(1, TNode::Call, 1, std::vector<std::shared_ptr<TNode>>());
  CallEntity call_entity = CallEntity(mock_call_node, 1);
  StatementStorage statement_storage;
  statement_storage.Clear();
  statement_storage.AddCallStatement(call_entity);
  std::unordered_set<std::string> call_list =
      statement_storage.GetCallStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  REQUIRE(call_list.size() == 1);
  REQUIRE(call_list.find("1") != call_list.end());
  REQUIRE(statement_list.size() == 1);
  REQUIRE(statement_list.find("1") != statement_list.end());
}

TEST_CASE("Read Storage Management", "[StatementStorage]") {
  TNode mock_read_node =
      TNode(2, TNode::Read, 2, std::vector<std::shared_ptr<TNode>>());
  ReadEntity read_entity = ReadEntity(mock_read_node, 2);
  StatementStorage statement_storage;
  statement_storage.Clear();
  statement_storage.AddReadStatement(read_entity);
  std::unordered_set<std::string> read_list =
      statement_storage.GetReadStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  REQUIRE(read_list.size() == 1);
  REQUIRE(read_list.find("2") != read_list.end());
  REQUIRE(statement_list.size() == 1);
  REQUIRE(statement_list.find("2") != statement_list.end());
}

TEST_CASE("Print Storage Management", "[StatementStorage]") {
  TNode mock_print_node =
      TNode(3, TNode::Print, 3, std::vector<std::shared_ptr<TNode>>());
  PrintEntity print_entity = PrintEntity(mock_print_node, 3);
  StatementStorage statement_storage;
  statement_storage.Clear();
  statement_storage.AddPrintStatement(print_entity);
  std::unordered_set<std::string> print_list =
      statement_storage.GetPrintStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  REQUIRE(print_list.size() == 1);
  REQUIRE(print_list.find("3") != print_list.end());
  REQUIRE(statement_list.size() == 1);
  REQUIRE(statement_list.find("3") != statement_list.end());
}

TEST_CASE("Assign Storage Management", "[StatementStorage]") {
  TNode mock_assign_node =
      TNode(4, TNode::Assign, 4, std::vector<std::shared_ptr<TNode>>());
  AssignEntity assign_entity = AssignEntity(mock_assign_node, 4);
  StatementStorage statement_storage;
  statement_storage.Clear();
  statement_storage.AddAssignStatement(assign_entity);
  std::unordered_set<std::string> assign_list =
      statement_storage.GetAssignStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  REQUIRE(assign_list.size() == 1);
  REQUIRE(assign_list.find("4") != assign_list.end());
  REQUIRE(statement_list.size() == 1);
  REQUIRE(statement_list.find("4") != statement_list.end());
}

TEST_CASE("If Storage Management", "[StatementStorage]") {
  TNode mock_if_node =
      TNode(5, TNode::IfElseThen, 5, std::vector<std::shared_ptr<TNode>>());
  IfEntity if_entity = IfEntity(mock_if_node, 5);
  StatementStorage statement_storage;
  statement_storage.Clear();
  statement_storage.AddIfStatement(if_entity);
  std::unordered_set<std::string> if_list = statement_storage.GetIfStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  REQUIRE(if_list.size() == 1);
  REQUIRE(if_list.find("5") != if_list.end());
  REQUIRE(statement_list.size() == 1);
  REQUIRE(statement_list.find("5") != statement_list.end());
}

TEST_CASE("While Storage Management", "[StatementStorage]") {
  TNode mock_while_node =
      TNode(6, TNode::While, 6, std::vector<std::shared_ptr<TNode>>());
  WhileEntity while_entity = WhileEntity(mock_while_node, 6);
  StatementStorage statement_storage;
  statement_storage.Clear();
  statement_storage.AddWhileStatement(while_entity);
  std::unordered_set<std::string> while_list =
      statement_storage.GetWhileStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  REQUIRE(while_list.size() == 1);
  REQUIRE(while_list.find("6") != while_list.end());
  REQUIRE(statement_list.size() == 1);
  REQUIRE(statement_list.find("6") != statement_list.end());
}

TEST_CASE("Clearing Statement Lists", "[StatementStorage]") {
  TNode mock_call_node =
      TNode(1, TNode::Call, 1, std::vector<std::shared_ptr<TNode>>());
  CallEntity call_entity = CallEntity(mock_call_node, 1);
  TNode mock_read_node =
      TNode(2, TNode::Read, 2, std::vector<std::shared_ptr<TNode>>());
  ReadEntity read_entity = ReadEntity(mock_read_node, 2);
  TNode mock_print_node =
      TNode(3, TNode::Print, 3, std::vector<std::shared_ptr<TNode>>());
  PrintEntity print_entity = PrintEntity(mock_print_node, 3);
  TNode mock_assign_node =
      TNode(4, TNode::Assign, 4, std::vector<std::shared_ptr<TNode>>());
  AssignEntity assign_entity = AssignEntity(mock_assign_node, 4);
  TNode mock_if_node =
      TNode(5, TNode::IfElseThen, 5, std::vector<std::shared_ptr<TNode>>());
  IfEntity if_entity = IfEntity(mock_if_node, 5);
  TNode mock_while_node =
      TNode(6, TNode::While, 6, std::vector<std::shared_ptr<TNode>>());
  WhileEntity while_entity = WhileEntity(mock_while_node, 6);
  StatementStorage statement_storage;
  statement_storage.AddCallStatement(call_entity);
  statement_storage.AddReadStatement(read_entity);
  statement_storage.AddPrintStatement(print_entity);
  statement_storage.AddAssignStatement(assign_entity);
  statement_storage.AddIfStatement(if_entity);
  statement_storage.AddWhileStatement(while_entity);
  statement_storage.Clear();
  std::unordered_set<std::string> call_list =
      statement_storage.GetCallStatements();
  std::unordered_set<std::string> read_list =
      statement_storage.GetReadStatements();
  std::unordered_set<std::string> print_list =
      statement_storage.GetPrintStatements();
  std::unordered_set<std::string> assign_list =
      statement_storage.GetAssignStatements();
  std::unordered_set<std::string> if_list = statement_storage.GetIfStatements();
  std::unordered_set<std::string> while_list =
      statement_storage.GetWhileStatements();
  std::unordered_set<std::string> statement_list =
      statement_storage.GetStatements();
  statement_storage.Clear();
  REQUIRE(call_list.size() == 0);
  REQUIRE(read_list.size() == 0);
  REQUIRE(print_list.size() == 0);
  REQUIRE(assign_list.size() == 0);
  REQUIRE(if_list.size() == 0);
  REQUIRE(while_list.size() == 0);
  REQUIRE(statement_list.size() == 0);
}
