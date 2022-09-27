#include "catch.hpp"
#include "pkb/relationship_store/calls_storage.h"

TEST_CASE("Calls Storage Management Single Child", "[CallsStorage]") {
  TNode mock_procedure_node_one =
      TNode(1, TNode::Procedure, 1, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_caller_one =
      ProcedureEntity(mock_procedure_node_one, "First");
  TNode mock_procedure_node_two =
      TNode(2, TNode::Procedure, 2, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_callee_one =
      ProcedureEntity(mock_procedure_node_two, "Second");
  TNode mock_procedure_node_three =
      TNode(3, TNode::Procedure, 3, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_caller_two =
      ProcedureEntity(mock_procedure_node_three, "Third");
  TNode mock_procedure_node_four =
      TNode(4, TNode::Procedure, 4, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_callee_two =
      ProcedureEntity(mock_procedure_node_four, "Fourth");
  CallsAbstraction mock_calls_abstraction_one =
      CallsAbstraction(mock_caller_one, mock_callee_one);
  CallsAbstraction mock_calls_abstraction_two =
      CallsAbstraction(mock_caller_two, mock_callee_two);
  CallsStorage calls_storage;
  calls_storage.AddRelationship(mock_calls_abstraction_one);
  calls_storage.AddRelationship(mock_calls_abstraction_two);
  std::unordered_set<std::string> callee_list =
      calls_storage.GetCallsProcedures("Second");
  std::unordered_set<std::string> caller_list =
      calls_storage.GetCallsByProcedures("First");
  std::unordered_set<std::string> all_callee_list =
      calls_storage.GetCallsProcedures();
  std::unordered_set<std::string> all_caller_list =
      calls_storage.GetCallsByProcedures();
  std::unordered_set<std::string> invalid_list =
      calls_storage.GetCallsProcedures("First");
  REQUIRE(*callee_list.find("First") == "First");
  REQUIRE(*caller_list.find("Second") == "Second");
  REQUIRE(all_callee_list.size() == 2);
  REQUIRE(all_callee_list.size() == all_caller_list.size());
  REQUIRE(invalid_list.empty());
}

TEST_CASE("Calls Storage Management Multi Callee", "[CallsStorage]") {
  TNode mock_procedure_node_one =
      TNode(1, TNode::Procedure, 1, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_caller_one =
      ProcedureEntity(mock_procedure_node_one, "First");
  TNode mock_procedure_node_two =
      TNode(2, TNode::Procedure, 2, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_callee_one =
      ProcedureEntity(mock_procedure_node_two, "Second");
  TNode mock_procedure_node_three =
      TNode(3, TNode::Procedure, 3, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_caller_two =
      ProcedureEntity(mock_procedure_node_three, "Third");
  TNode mock_procedure_node_four =
      TNode(4, TNode::Procedure, 4, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_callee_two =
      ProcedureEntity(mock_procedure_node_four, "Fourth");
  CallsAbstraction mock_calls_abstraction_one =
      CallsAbstraction(mock_caller_one, mock_callee_one);
  CallsAbstraction mock_calls_abstraction_two =
      CallsAbstraction(mock_caller_one, mock_caller_two);
  CallsAbstraction mock_calls_abstraction_three =
      CallsAbstraction(mock_caller_one, mock_callee_two);
  CallsStorage calls_storage;
  calls_storage.AddRelationship(mock_calls_abstraction_one);
  calls_storage.AddRelationship(mock_calls_abstraction_two);
  calls_storage.AddRelationship(mock_calls_abstraction_three);
  std::unordered_set<std::string> caller_list =
      calls_storage.GetCallsProcedures("Second");
  std::unordered_set<std::string> callee_list =
      calls_storage.GetCallsByProcedures("First");
  std::unordered_set<std::string> all_caller_list =
      calls_storage.GetCallsProcedures();
  std::unordered_set<std::string> all_callee_list =
      calls_storage.GetCallsByProcedures();
  std::unordered_set<std::string> invalid_list =
      calls_storage.GetCallsProcedures("First");
  REQUIRE(*caller_list.find("First") == "First");
  REQUIRE(*callee_list.find("Second") == "Second");
  REQUIRE(*callee_list.find("Third") == "Third");
  REQUIRE(*callee_list.find("Fourth") == "Fourth");
  REQUIRE(*all_caller_list.find("First") == "First");
  REQUIRE(*all_callee_list.find("Second") == "Second");
  REQUIRE(*all_callee_list.find("Third") == "Third");
  REQUIRE(*all_callee_list.find("Fourth") == "Fourth");
  REQUIRE(invalid_list.empty());
}

TEST_CASE("Calls Storage Management Multi Caller", "[CallsStorage]") {
  TNode mock_procedure_node_one =
      TNode(1, TNode::Procedure, 1, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_caller_one =
      ProcedureEntity(mock_procedure_node_one, "First");
  TNode mock_procedure_node_two =
      TNode(2, TNode::Procedure, 2, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_callee_one =
      ProcedureEntity(mock_procedure_node_two, "Second");
  TNode mock_procedure_node_three =
      TNode(3, TNode::Procedure, 3, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_caller_two =
      ProcedureEntity(mock_procedure_node_three, "Third");
  TNode mock_procedure_node_four =
      TNode(4, TNode::Procedure, 4, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_callee_two =
      ProcedureEntity(mock_procedure_node_four, "Fourth");
  CallsAbstraction mock_calls_abstraction_one =
      CallsAbstraction(mock_caller_one, mock_callee_one);
  CallsAbstraction mock_calls_abstraction_two =
      CallsAbstraction(mock_caller_two, mock_callee_one);
  CallsAbstraction mock_calls_abstraction_three =
      CallsAbstraction(mock_caller_one, mock_callee_two);
  CallsAbstraction mock_calls_abstraction_four =
      CallsAbstraction(mock_caller_two, mock_callee_two);
  CallsStorage calls_storage;
  calls_storage.AddRelationship(mock_calls_abstraction_one);
  calls_storage.AddRelationship(mock_calls_abstraction_two);
  calls_storage.AddRelationship(mock_calls_abstraction_three);
  calls_storage.AddRelationship(mock_calls_abstraction_four);
  std::unordered_set<std::string> caller_list_one =
      calls_storage.GetCallsProcedures("Second");
  std::unordered_set<std::string> caller_list_two =
      calls_storage.GetCallsProcedures("Fourth");
  std::unordered_set<std::string> callee_list =
      calls_storage.GetCallsByProcedures("First");
  std::unordered_set<std::string> all_caller_list =
      calls_storage.GetCallsProcedures();
  std::unordered_set<std::string> all_callee_list =
      calls_storage.GetCallsByProcedures();
  std::unordered_set<std::string> invalid_list =
      calls_storage.GetCallsProcedures("First");
  REQUIRE(*caller_list_one.find("First") == "First");
  REQUIRE(*caller_list_one.find("Third") == "Third");
  REQUIRE(*caller_list_two.find("First") == "First");
  REQUIRE(*caller_list_two.find("Third") == "Third");
  REQUIRE(*callee_list.find("Second") == "Second");
  REQUIRE(*callee_list.find("Fourth") == "Fourth");
  REQUIRE(*all_caller_list.find("First") == "First");
  REQUIRE(*all_caller_list.find("Third") == "Third");
  REQUIRE(*all_callee_list.find("Second") == "Second");
  REQUIRE(*all_callee_list.find("Fourth") == "Fourth");
  REQUIRE(invalid_list.empty());
}

/*** ============================
 * This tests the storage of the case where First calls Second, Second calls
 * Third, meaning First CallsT Third
 * ============================== */
TEST_CASE("CallsT Storage Management", "[CallsStorage]") {
  TNode mock_procedure_node_one =
      TNode(1, TNode::Procedure, 1, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_procedure_one =
      ProcedureEntity(mock_procedure_node_one, "First");
  TNode mock_procedure_node_two =
      TNode(2, TNode::Procedure, 2, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_procedure_two =
      ProcedureEntity(mock_procedure_node_two, "Second");
  TNode mock_procedure_node_three =
      TNode(3, TNode::Procedure, 3, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity mock_procedure_three =
      ProcedureEntity(mock_procedure_node_three, "Third");
  CallsTAbstraction mock_calls_abstraction_one =
      CallsTAbstraction(mock_procedure_one, mock_procedure_two);
  CallsTAbstraction mock_calls_abstraction_two =
      CallsTAbstraction(mock_procedure_two, mock_procedure_three);
  CallsTAbstraction mock_calls_abstraction_three =
      CallsTAbstraction(mock_procedure_one, mock_procedure_three);
  CallsStorage calls_storage;
  calls_storage.AddRelationship(mock_calls_abstraction_one);
  calls_storage.AddRelationship(mock_calls_abstraction_two);
  calls_storage.AddRelationship(mock_calls_abstraction_three);
  std::unordered_set<std::string> caller_list_one =
      calls_storage.GetCallsTProcedures("Second");
  std::unordered_set<std::string> caller_list_two =
      calls_storage.GetCallsTProcedures("Third");
  std::unordered_set<std::string> callee_list =
      calls_storage.GetCallsTByProcedures("First");
  std::unordered_set<std::string> invalid_list =
      calls_storage.GetCallsTProcedures("First");
  REQUIRE(*caller_list_one.find("First") == "First");
  REQUIRE(*caller_list_two.find("First") == "First");
  REQUIRE(*caller_list_two.find("Second") == "Second");
  REQUIRE(*callee_list.find("Second") == "Second");
  REQUIRE(*callee_list.find("Third") == "Third");
  REQUIRE(invalid_list.empty());
}
