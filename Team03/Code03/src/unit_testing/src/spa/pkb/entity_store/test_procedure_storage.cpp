#include "catch.hpp"
#include "pkb/entity_store/procedure_storage.h"

TEST_CASE("Procedure Storage Management", "[ProcedureStorage]") {
  TNode mock_procedure_node =
      TNode(1, TNode::Procedure, 1, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity procedure_entity =
      ProcedureEntity(mock_procedure_node, "TESTPROC");
  ProcedureStorage procedure_storage;
  procedure_storage.AddProcedure(procedure_entity);
  std::unordered_set<std::string> procedure_list =
      procedure_storage.GetProcedures();
  REQUIRE(procedure_list.find("TESTPROC") != procedure_list.end());
}

TEST_CASE("Clearing Procedure List", "[ProcedureStorage]") {
  TNode mock_procedure_node =
      TNode(1, TNode::Procedure, 1, std::vector<std::shared_ptr<TNode>>());
  ProcedureEntity procedure_entity =
      ProcedureEntity(mock_procedure_node, "TESTPROC");
  ProcedureStorage procedure_storage;
  procedure_storage.AddProcedure(procedure_entity);
  procedure_storage.Clear();
  std::unordered_set<std::string> procedure_list =
      procedure_storage.GetProcedures();
  REQUIRE(procedure_list.find("TESTPROC") == procedure_list.end());
}
