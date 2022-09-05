#include "catch.hpp"
#include "pkb/entity_store/statement_storage.h"

TEST_CASE("Call Storage Management", "[StatementStorage]") {
    TNode mock_call_node =
            TNode(1, TNode::Call, 1, std::vector<std::shared_ptr<TNode>>());
    CallEntity call_entity = CallEntity(mock_call_node, 1);
    StatementStorage statement_storage;
    statement_storage.addCallStatement(call_entity);
    std::unordered_set<std::string> call_list = statement_storage.getCallStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
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
    statement_storage.addReadStatement(read_entity);
    std::unordered_set<std::string> read_list = statement_storage.getReadStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
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
    statement_storage.addPrintStatement(print_entity);
    std::unordered_set<std::string> print_list = statement_storage.getPrintStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
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
    statement_storage.addAssignStatement(assign_entity);
    std::unordered_set<std::string> assign_list = statement_storage.getAssignStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
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
    statement_storage.addIfStatement(if_entity);
    std::unordered_set<std::string> if_list = statement_storage.getIfStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
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
    statement_storage.addWhileStatement(while_entity);
    std::unordered_set<std::string> while_list = statement_storage.getWhileStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
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
    statement_storage.addCallStatement(call_entity);
    statement_storage.addReadStatement(read_entity);
    statement_storage.addPrintStatement(print_entity);
    statement_storage.addAssignStatement(assign_entity);
    statement_storage.addIfStatement(if_entity);
    statement_storage.addWhileStatement(while_entity);
    statement_storage.clear();
    std::unordered_set<std::string> call_list = statement_storage.getCallStatements();
    std::unordered_set<std::string> read_list = statement_storage.getReadStatements();
    std::unordered_set<std::string> print_list = statement_storage.getPrintStatements();
    std::unordered_set<std::string> assign_list = statement_storage.getAssignStatements();
    std::unordered_set<std::string> if_list = statement_storage.getIfStatements();
    std::unordered_set<std::string> while_list = statement_storage.getWhileStatements();
    std::unordered_set<std::string> statement_list = statement_storage.getStatements();
    statement_storage.clear();
    REQUIRE(call_list.size() == 0);
    REQUIRE(read_list.size() == 0);
    REQUIRE(print_list.size() == 0);
    REQUIRE(assign_list.size() == 0);
    REQUIRE(if_list.size() == 0);
    REQUIRE(while_list.size() == 0);
    REQUIRE(statement_list.size() == 0);
}
